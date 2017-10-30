/**
 * @file        CommandIF.c
 * @brief       �R�}���h�C���^�t�F�[�X�ʐM���C�u����
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
 * @brief   �R�}���h�𑗐M����
 * @param[in]       cmdIF               �R�}���h�C���^�t�F�[�X���\����
 * @param[in]       commandOpcode       �R�}���h�I�y�R�[�h
 * @param[in]       commandOperand      �R�}���h�I�y�����h�i�[��̃|�C���^
 * @param[in]       commandOperandSize  �R�}���h�I�y�����h�̃T�C�Y
 * @retval          TRUE                ����I��
 * @retval          FALSE               �ُ�I��
 */
static BOOL CommandIF_sendCommand(COMMANDIF_T *cmdIF, BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandSize);


/**
 * @brief   �R�}���h�𐶐�����
 * @param[in]       commandOpcode       �R�}���h�I�y�R�[�h
 * @param[in]       commandOperand      �R�}���h�I�y�����h�i�[��̃|�C���^
 * @param[in]       commandOperandSize  �R�}���h�I�y�����h�̃T�C�Y
 * @param[out]      commandBytes        �R�}���h��
 * @return          �R�}���h
 */
static LPBYTE CommandIF_createCommand(BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandSize, LPDWORD commandBytes);


/**
 * @brief   ���X�|���X����M����
 * @param[in]       cmdIF               �R�}���h�C���^�t�F�[�X���\����
 * @return          ���X�|���X
 */
static LPBYTE CommandIF_receiveResponse(COMMANDIF_T *cmdIF);


/**
 * @brief   ���X�|���X�w�b�_����R�}���h���s���ʂ��擾����
 * @param[in]       response            ���X�|���X
 * @return          �R�}���h���s����
 */
static BYTE CommandIF_getCommandResult(LPBYTE response);


/**
 * @brief   ���X�|���X�w�b�_���烌�X�|���X�����擾����
 * @param[in]       response            ���X�|���X
 * @return          ���X�|���X��
 */
static DWORD CommandIF_getResponseBytes(LPBYTE response);


BOOL CommandIF_open(COMMANDIF_T *cmdIF, LPCTSTR comName)
{
    BOOL retval;
    BOOL result;

    result = TRUE;

    if (cmdIF != NULL) {
        /* �V���A���|�[�g�̃n���h���̏����� */
        cmdIF->comPort.comHandle = INVALID_HANDLE_VALUE;

        /* �V���A���|�[�g�̐���ݒ�i�R�}���h�C���^�t�F�[�X�����j */
        cmdIF->comPort.comRxBufSize = 8192;
        cmdIF->comPort.comTxBufSize = 8192;
        cmdIF->comPort.comBaudRate = CBR_9600;
        cmdIF->comPort.comByteSize = 8;
        cmdIF->comPort.comParity = NOPARITY;
        cmdIF->comPort.comStopBits = ONESTOPBIT;

        /* �f�o�C�X���̏����� */
        cmdIF->deviceType = 0;
        cmdIF->deviceVersion = 0;
        cmdIF->deviceRevision = 0;

        /* �V���A���|�[�g���J�� */
        retval = ComPort_openComPort(&(cmdIF->comPort), comName);
        if (retval == FALSE) {
            result = FALSE;
        }
    }
    else {
        result = FALSE;
    }

    return result;
}


BOOL CommandIF_close(COMMANDIF_T *cmdIF)
{
    BOOL result;

    result = TRUE;

    if (cmdIF != NULL) {
        result = ComPort_closeComPort(&(cmdIF->comPort));
    }

    return result;
}


BOOL CommandIF_execCommand_ResetDevice(COMMANDIF_T *cmdIF)
{
    return CommandIF_sendCommand(cmdIF, COMMAND_RESET, NULL, 0);
}


BOOL CommandIF_execCommand_InitializeSystem(COMMANDIF_T *cmdIF)
{
    return CommandIF_sendCommand(cmdIF, COMMAND_INITIALIZE, NULL, 0);
}


BOOL CommandIF_execCommand_GetVersion(COMMANDIF_T *cmdIF)
{
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* �R�}���h�𑗐M */
    retval = CommandIF_sendCommand(cmdIF, COMMAND_GET_VERSION, NULL, 0);
        
    /* �R�}���h���X�|���X����M */
    if (retval == TRUE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* ���X�|���X����R�}���h���s���ʂ��擾 */
            commandResult = CommandIF_getCommandResult(response);

            /* ���X�|���X���烌�X�|���X�����擾 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* ���X�|���X����o�[�W���������擾 */
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


LPBYTE CommandIF_execCommand_ReadRegister(COMMANDIF_T *cmdIF, DWORD registerIndex, LPDWORD readBytes)
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

    /* �R�}���h�𑗐M */
    commandOperand = (BYTE)registerIndex;
    retval = CommandIF_sendCommand(
        cmdIF,
        COMMAND_READ_REGISTER,
        &commandOperand,
        1
    );

    /* �R�}���h���X�|���X����M */
    if (retval == TRUE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response != NULL) {
            /* ���X�|���X����R�}���h���s���ʂ��擾 */
            commandResult = CommandIF_getCommandResult(response);

            /* ���X�|���X���烌�X�|���X�����擾 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* ���X�|���X������Ǎ��݃o�C�g�����Z�o */
            if ((commandResult == 0) && (responseBytes > 2)) {
                readBytesTemp = responseBytes - 2;
            }
            else {
                readBytesTemp = 0;
            }

            /* ���W�X�^�Ǎ��݌��ʂ��i�[ */
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


BOOL CommandIF_execCommand_WriteRegister(COMMANDIF_T *cmdIF, DWORD registerIndex, LPVOID data, DWORD dataBytes)
{
    DWORD commandOperandBytes;
    LPBYTE commandOperand;
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* �I�y�����h�p�̃������̈���m�� */
    commandOperandBytes = 1 + dataBytes;
    commandOperand = (LPBYTE)malloc(sizeof(BYTE) * commandOperandBytes);
    if (commandOperand != NULL) {
        /* �I�y�����h���쐬 */
        memset(commandOperand, 0x00, (sizeof(BYTE) * commandOperandBytes));
        commandOperand[0] = (BYTE)registerIndex;
        memcpy(&commandOperand[1], data, (sizeof(BYTE) * dataBytes));

        /* �R�}���h�𑗐M */
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

    /* �R�}���h���X�|���X����M */
    if (retval == TRUE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* ���X�|���X����R�}���h���s���ʂ��擾 */
            commandResult = CommandIF_getCommandResult(response);

            /* ���X�|���X���烌�X�|���X�����擾 */
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


LPBYTE CommandIF_execCommand_ReadEEPROM(COMMANDIF_T *cmdIF, DWORD eepromIndex, LPDWORD readBytes)
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

    /* �R�}���h�𑗐M */
    commandOperand = (BYTE)eepromIndex;
    retval = CommandIF_sendCommand(
        cmdIF,
        COMMAND_READ_EEPROM,
        &commandOperand,
        1
    );

    /* �R�}���h���X�|���X����M */
    if (retval == TRUE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response != NULL) {
            /* ���X�|���X����R�}���h���s���ʂ��擾 */
            commandResult = CommandIF_getCommandResult(response);

            /* ���X�|���X���烌�X�|���X�����擾 */
            responseBytes = CommandIF_getResponseBytes(response);

            /* ���X�|���X������Ǎ��݃o�C�g�����Z�o */
            if ((commandResult == 0) && (responseBytes > 2)) {
                readBytesTemp = responseBytes - 2;
            }
            else {
                readBytesTemp = 0;
            }

            /* EEPROM�Ǎ��݌��ʂ��i�[ */
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


BOOL CommandIF_execCommand_WriteEEPROM(COMMANDIF_T *cmdIF, DWORD eepromIndex, LPVOID data, DWORD dataBytes)
{
    DWORD commandOperandBytes;
    LPBYTE commandOperand;
    BYTE commandResult;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;
    BOOL result;

    result = TRUE;

    /* �I�y�����h�p�̃������̈���m�� */
    commandOperandBytes = 1 + dataBytes;
    commandOperand = (LPBYTE)malloc(sizeof(BYTE) * commandOperandBytes);
    if (commandOperand != NULL) {
        /* �I�y�����h���쐬 */
        memset(commandOperand, 0x00, (sizeof(BYTE) * commandOperandBytes));
        commandOperand[0] = (BYTE)eepromIndex;
        memcpy(&commandOperand[1], data, (sizeof(BYTE) * dataBytes));

        /* �R�}���h�𑗐M */
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

    /* �R�}���h���X�|���X����M */
    if (retval == TRUE) {
        response = CommandIF_receiveResponse(cmdIF);
        if (response == NULL) {
            result = FALSE;
        }
        else {
            /* ���X�|���X����R�}���h���s���ʂ��擾 */
            commandResult = CommandIF_getCommandResult(response);

            /* ���X�|���X���烌�X�|���X�����擾 */
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


static BOOL CommandIF_sendCommand(COMMANDIF_T *cmdIF, BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandSize)
{
    LPBYTE command;
    DWORD commandBytes;
    BOOL result;

    result = TRUE;

    if (cmdIF->comPort.comHandle != INVALID_HANDLE_VALUE) {
        /* �R�}���h���쐬 */
        command = CommandIF_createCommand(commandOpcode, commandOperand, commandOperandSize, &commandBytes);

        /* �R�}���h�𑗐M */
        if (command != NULL) {
            result = ComPort_writeData(
                &(cmdIF->comPort),
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


static LPBYTE CommandIF_createCommand(BYTE commandOpcode, LPBYTE commandOperand, DWORD commandOperandSize, LPDWORD commandBytes)
{
    LPBYTE commandTemp;
    DWORD commandBytesTemp;

    *commandBytes = 0;
    commandTemp = NULL;

    if ((commandOperandSize >= 0) && (commandOperandSize <= COMMAND_OPERAND_LENGTH_MAX)) {
        /* �R�}���h�����Z�o */
        commandBytesTemp = COMMAND_OPCODE_LENGTH + commandOperandSize;

        /* �R�}���h�p�̃������̈���m�� */
        commandTemp = (LPBYTE)malloc(sizeof(BYTE) * commandBytesTemp);
        if (commandTemp != NULL) {
            memset(commandTemp, 0x00, (sizeof(BYTE) * commandBytesTemp));

            /* �I�y�R�[�h��ݒ� */
            commandTemp[0] = (commandOpcode << 4) | (BYTE)commandBytesTemp;

            /* �I�y�����h��ݒ� */
            if (commandOperandSize > 0) {
                if (commandOperand != NULL) {
                    memcpy(&commandTemp[1], commandOperand, (sizeof(BYTE) * commandOperandSize));
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


static LPBYTE CommandIF_receiveResponse(COMMANDIF_T *cmdIF)
{
    BYTE responseHeader;
    DWORD responseBytes;
    LPBYTE response;
    BOOL retval;

    response = NULL;

    if (cmdIF->comPort.comHandle != INVALID_HANDLE_VALUE) {
        /* ���X�|���X�w�b�_����M */
        responseHeader = 0x00;
        retval = ComPort_readData(
            &(cmdIF->comPort),
            &responseHeader,
            1
        );

        /* ���X�|���X�w�b�_���烌�X�|���X�����擾 */
        if (retval == TRUE) {
            responseBytes = CommandIF_getResponseBytes(&responseHeader);
        }
        else {
            responseBytes = 0;
        }

        /* ���X�|���X�p�̃������̈���m�� */
        if (responseBytes > 0) {
            response = (LPBYTE)malloc(sizeof(BYTE) * responseBytes);
            if (response != NULL) {
                memset(response, 0x00, (sizeof(BYTE) * responseBytes));
                response[0] = responseHeader;
            }
        }

        /* ���X�|���X�̑�������M */
        if ((response != NULL) && (responseBytes > 1)) {
            retval = ComPort_readData(
                &(cmdIF->comPort),
                &response[1],
                (responseBytes - 1)
            );
            if (retval != TRUE) {
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
