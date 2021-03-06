/**
 * @file        CommandIF.c
 * @brief       コマンドインタフェース通信ライブラリ
 * @author      Keitetsu
 * @date        2016/04/11
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include "ComPort.h"

#include "CommandIF_Command.h"

#include "CommandIF.h"


/**
 * @brief   コマンドを送信する
 * @param[in]       cmdIF               コマンドインタフェース情報構造体のポインタ
 * @param[in]       commandOpcode       コマンドオペコード
 * @param[in]       commandOperand      コマンドオペランド格納先のポインタ
 * @param[in]       commandOperandBytes コマンドオペランドのバイト数
 * @retval          TRUE                正常終了
 * @retval          FALSE               異常終了
 */
static BOOL CommandIF_sendCommand(COMMANDIF cmdIF, BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandBytes);


/**
 * @brief   コマンドを生成する
 * @param[in]       commandOpcode       コマンドオペコード
 * @param[in]       commandOperand      コマンドオペランド格納先のポインタ
 * @param[in]       commandOperandBytes コマンドオペランドのバイト数
 * @param[out]      commandBytes        コマンド長
 * @return          コマンド
 */
static LPBYTE CommandIF_createCommand(BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandBytes, LPDWORD commandBytes);


/**
 * @brief   レスポンスを受信する
 * @param[in]       cmdIF               コマンドインタフェース情報構造体のポインタ
 * @return          レスポンス
 */
static LPBYTE CommandIF_receiveResponse(COMMANDIF cmdIF);


/**
 * @brief   レスポンスヘッダからコマンド実行結果を取得する
 * @param[in]       response            レスポンス
 * @return          コマンド実行結果
 */
static BYTE CommandIF_getCommandResult(LPBYTE response);


/**
 * @brief   レスポンスヘッダからレスポンス長を取得する
 * @param[in]       response            レスポンス
 * @return          レスポンス長
 */
static DWORD CommandIF_getResponseBytes(LPBYTE response);


COMMANDIF CommandIF_open(LPCTSTR comName)
{
    COMMANDIF cmdIF;

    /* インスタンスの生成 */
    cmdIF = (COMMANDIF)malloc(sizeof(COMMANDIF_T));
    if (cmdIF == NULL) {
        return NULL;
    }
    ZeroMemory(cmdIF, sizeof(COMMANDIF_T));

    /* デバイス情報の初期化 */
    cmdIF->deviceType = 0;
    cmdIF->deviceVersion = 0;
    cmdIF->deviceRevision = 0;

    /* シリアルポートを開く */
    cmdIF->comPort = ComPort_openComPort(comName, CBR_9600);
    if (cmdIF->comPort == NULL) {
        free(cmdIF);
        return NULL;
    }
    
    /* シリアルポートの制御設定（コマンドインタフェース向け） */
    cmdIF->comPort->comBaudRate = CBR_9600;
    cmdIF->comPort->comByteSize = 8;
    cmdIF->comPort->comParity = NOPARITY;
    cmdIF->comPort->comStopBits = ONESTOPBIT;
    ComPort_setDCB(cmdIF->comPort);

    return cmdIF;
}


COMMANDIF CommandIF_close(COMMANDIF cmdIF)
{
    if (cmdIF != NULL) {
        ComPort_closeComPort(cmdIF->comPort);
        free(cmdIF);
        cmdIF = NULL;
    }

    return cmdIF;
}


BOOL CommandIF_execCommand_ResetDevice(COMMANDIF cmdIF)
{
    return CommandIF_sendCommand(cmdIF, COMMAND_RESET, NULL, 0);
}


BOOL CommandIF_execCommand_InitializeSystem(COMMANDIF cmdIF)
{
    return CommandIF_sendCommand(cmdIF, COMMAND_INITIALIZE, NULL, 0);
}


BOOL CommandIF_execCommand_GetVersion(COMMANDIF cmdIF)
{
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* コマンドを送信 */
    retval = CommandIF_sendCommand(cmdIF, COMMAND_GET_VERSION, NULL, 0);
        
    /* コマンドレスポンスを受信 */
    if (retval != FALSE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* レスポンスからコマンド実行結果を取得 */
            commandResult = CommandIF_getCommandResult(response);

            /* レスポンスからレスポンス長を取得 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* レスポンスからバージョン情報を取得 */
            if ((commandResult == 0) && (responseBytes == 4)) {
                cmdIF->deviceType = response[1];
                cmdIF->deviceVersion = response[2];
                cmdIF->deviceRevision = response[3];
            }
            else {
                result = FALSE;
            }
        }
        free(response);
    }

    return result;
}


LPBYTE CommandIF_execCommand_ReadRegister(COMMANDIF cmdIF, DWORD registerIndex, LPDWORD readBytes)
{
    BYTE commandOperand;
    LPBYTE response;
    BYTE commandResult;
    DWORD responseBytes;
    DWORD readBytesTemp;
    LPBYTE registerData;
    BOOL retval;

    *readBytes = 0;
    registerData = NULL;

    /* コマンドを送信 */
    commandOperand = (BYTE)registerIndex;
    retval = CommandIF_sendCommand(
        cmdIF,
        COMMAND_READ_REGISTER,
        &commandOperand,
        1
    );

    /* コマンドレスポンスを受信 */
    if (retval != FALSE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response != NULL) {
            /* レスポンスからコマンド実行結果を取得 */
            commandResult = CommandIF_getCommandResult(response);

            /* レスポンスからレスポンス長を取得 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* レスポンス長から読込みバイト数を算出 */
            if ((commandResult == 0) && (responseBytes > 2)) {
                readBytesTemp = responseBytes - 2;
            }
            else {
                readBytesTemp = 0;
            }

            /* レジスタ読込み結果を格納 */
            if (readBytesTemp > 0) {
                registerData = (LPBYTE)malloc(sizeof(BYTE) * readBytesTemp);
                if (registerData != NULL) {
                    memcpy(registerData, &response[2], (sizeof(BYTE) * readBytesTemp));
                    *readBytes = readBytesTemp;
                }
            }
        }
        free(response);
    }

    return registerData;
}


BOOL CommandIF_execCommand_WriteRegister(COMMANDIF cmdIF, DWORD registerIndex, LPVOID data, DWORD dataBytes)
{
    DWORD commandOperandBytes;
    LPBYTE commandOperand;
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* オペランド用のメモリ領域を確保 */
    commandOperandBytes = 1 + dataBytes;
    commandOperand = (LPBYTE)malloc(sizeof(BYTE) * commandOperandBytes);
    if (commandOperand != NULL) {
        /* オペランドを作成 */
        memset(commandOperand, 0x00, (sizeof(BYTE) * commandOperandBytes));
        commandOperand[0] = (BYTE)registerIndex;
        memcpy(&commandOperand[1], data, (sizeof(BYTE) * dataBytes));

        /* コマンドを送信 */
        retval = CommandIF_sendCommand(
            cmdIF,
            COMMAND_WRITE_REGISTER,
            commandOperand,
            commandOperandBytes
        );
        free(commandOperand);
    }
    else {
        retval = FALSE;
    }

    /* コマンドレスポンスを受信 */
    if (retval != FALSE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* レスポンスからコマンド実行結果を取得 */
            commandResult = CommandIF_getCommandResult(response);

            /* レスポンスからレスポンス長を取得 */
            responseBytes = CommandIF_getResponseBytes(response);

            if ((commandResult == 0) && (responseBytes == 2)) {
                if (response[1] != dataBytes) {
                    result = FALSE;
                }
            }
            else {
                result = FALSE;
            }
            free(response);
        }
    }
    else {
        result = FALSE;
    }

    return result;
}


LPBYTE CommandIF_execCommand_ReadEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPDWORD readBytes)
{
    BYTE commandOperand;
    LPBYTE response;
    BYTE commandResult;
    DWORD responseBytes;
    DWORD readBytesTemp;
    LPBYTE eepromData;
    BOOL retval;

    *readBytes = 0;
    eepromData = NULL;

    /* コマンドを送信 */
    commandOperand = (BYTE)eepromIndex;
    retval = CommandIF_sendCommand(
        cmdIF,
        COMMAND_READ_EEPROM,
        &commandOperand,
        1
    );

    /* コマンドレスポンスを受信 */
    if (retval != FALSE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response != NULL) {
            /* レスポンスからコマンド実行結果を取得 */
            commandResult = CommandIF_getCommandResult(response);

            /* レスポンスからレスポンス長を取得 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* レスポンス長から読込みバイト数を算出 */
            if ((commandResult == 0) && (responseBytes > 2)) {
                readBytesTemp = responseBytes - 2;
            }
            else {
                readBytesTemp = 0;
            }

            /* EEPROM読込み結果を格納 */
            if (readBytesTemp > 0) {
                eepromData = (LPBYTE)malloc(sizeof(BYTE) * readBytesTemp);
                if (eepromData != NULL) {
                    memcpy(eepromData, &response[2], (sizeof(BYTE) * readBytesTemp));
                    *readBytes = readBytesTemp;
                }
            }
        }
        free(response);
    }

    return eepromData;
}


BOOL CommandIF_execCommand_WriteEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPVOID data, DWORD dataBytes)
{
    DWORD commandOperandBytes;
    LPBYTE commandOperand;
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* オペランド用のメモリ領域を確保 */
    commandOperandBytes = 1 + dataBytes;
    commandOperand = (LPBYTE)malloc(sizeof(BYTE) * commandOperandBytes);
    if (commandOperand != NULL) {
        /* オペランドを作成 */
        memset(commandOperand, 0x00, (sizeof(BYTE) * commandOperandBytes));
        commandOperand[0] = (BYTE)eepromIndex;
        memcpy(&commandOperand[1], data, (sizeof(BYTE) * dataBytes));

        /* コマンドを送信 */
        retval = CommandIF_sendCommand(
            cmdIF,
            COMMAND_WRITE_EEPROM,
            commandOperand,
            commandOperandBytes
        );
        free(commandOperand);
    }
    else {
        retval = FALSE;
    }

    /* コマンドレスポンスを受信 */
    if (retval != FALSE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* レスポンスからコマンド実行結果を取得 */
            commandResult = CommandIF_getCommandResult(response);

            /* レスポンスからレスポンス長を取得 */
            responseBytes = CommandIF_getResponseBytes(response);

            if ((commandResult == 0) && (responseBytes == 2)) {
                if (response[1] != 1) {
                    result = FALSE;
                }
            }
            else {
                result = FALSE;
            }
            free(response);
        }
    }
    else {
        result = FALSE;
    }

    return result;
}


static BOOL CommandIF_sendCommand(COMMANDIF cmdIF, BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandBytes)
{
    LPBYTE command;
    DWORD commandBytes;
    BOOL result;

    result = TRUE;

    if (cmdIF->comPort->comHandle != INVALID_HANDLE_VALUE) {
        /* コマンドを作成 */
        command = CommandIF_createCommand(commandOpcode, commandOperand, commandOperandBytes, &commandBytes);

        /* コマンドを送信 */
        if (command != NULL) {
            result = ComPort_writeData(
                cmdIF->comPort,
                command,
                commandBytes
            );
            free(command);
        }
        else {
            result = FALSE;
        }
    }
    else {
        result = FALSE;
    }

    return result;
}


static LPBYTE CommandIF_createCommand(BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandBytes, LPDWORD commandBytes)
{
    LPBYTE commandTemp;
    DWORD commandBytesTemp;

    *commandBytes = 0;
    commandTemp = NULL;

    if ((commandOperandBytes >= 0) && (commandOperandBytes <= COMMAND_OPERAND_LENGTH_MAX)) {
        /* コマンド長を算出 */
        commandBytesTemp = COMMAND_OPCODE_LENGTH + commandOperandBytes;

        /* コマンド用のメモリ領域を確保 */
        commandTemp = (LPBYTE)malloc(sizeof(BYTE) * commandBytesTemp);
        if (commandTemp != NULL) {
            memset(commandTemp, 0x00, (sizeof(BYTE) * commandBytesTemp));

            /* オペコードを設定 */
            commandTemp[0] = (commandOpcode << 4) | (BYTE)commandBytesTemp;

            /* オペランドを設定 */
            if (commandOperandBytes > 0) {
                if (commandOperand != NULL) {
                    memcpy(&commandTemp[1], commandOperand, (sizeof(BYTE) * commandOperandBytes));
                }
                else {
                    free(commandTemp);
                    commandTemp = NULL;
                }
            }

            *commandBytes = commandBytesTemp;
        }
    }

    return commandTemp;
}


static LPBYTE CommandIF_receiveResponse(COMMANDIF cmdIF)
{
    BYTE responseHeader;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;

    response = NULL;

    if (cmdIF->comPort->comHandle != INVALID_HANDLE_VALUE) {
        /* レスポンスヘッダを受信 */
        responseHeader = 0x00;
        retval = ComPort_readData(
            cmdIF->comPort,
            &responseHeader,
            1
        );

        /* レスポンスヘッダからレスポンス長を取得 */
        if (retval != FALSE) {
            responseBytes = CommandIF_getResponseBytes(&responseHeader);
        }
        else {
            responseBytes = 0;
        }

        /* レスポンス用のメモリ領域を確保 */
        if (responseBytes > 0) {
            response = (LPBYTE)malloc(sizeof(BYTE) * responseBytes);
            if (response != NULL) {
                memset(response, 0x00, (sizeof(BYTE) * responseBytes));
                response[0] = responseHeader;
            }
        }

        /* レスポンスの続きを受信 */
        if ((response != NULL) && (responseBytes > 1)) {
            retval = ComPort_readData(
                cmdIF->comPort,
                &response[1],
                (responseBytes - 1)
            );
            if (retval == FALSE) {
                free(response);
                response = NULL;
            }
        }
    }

    return response;
}


static BYTE CommandIF_getCommandResult(LPBYTE response)
{
    return ((response[0] & RESPONSE_MASK_COMMAND_RESULT) >> 4);
}


static DWORD CommandIF_getResponseBytes(LPBYTE response)
{
    return (response[0] & RESPONSE_MASK_LENGTH);
}
