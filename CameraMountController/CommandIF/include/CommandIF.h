/**
 * @file        CommandIF.h
 * @brief       コマンドインタフェース通信ライブラリ
 * @author      Keitetsu
 * @date        2017/07/17
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_COMMANDIF_H__
#define __CAMERAMOUNT_COMMANDIF_H__

#include <stdint.h>

#include "ComPort.h"


/**
 * @name    コマンドフォーマット
 */
/*! @{ */
#define COMMAND_LENGTH_MAX              6       /*!< 最大コマンド長 */
/*! @} */


/**
 * @name    コマンドレスポンスフォーマット
 */
/*! @{ */
#define RESPONSE_LENGTH_MAX             6       /*!< 最大レスポンス長 */
/*! @} */


/**
 * @struct  CommandIF_st
 * @brief   コマンドインタフェース情報構造体
 *
 * @typedef COMMANDIF_T
 * @brief   コマンドインタフェース情報構造体
 */
typedef struct CommandIF_st {
    COMPORT_T comPort;              /*!< シリアルポート情報構造体 */
    uint8_t deviceType;             /*!< デバイスタイプ */
    uint8_t deviceVersion;          /*!< デバイスバージョン */
    uint8_t deviceRevision;         /*!< デバイスリビジョン */
} COMMANDIF_T;


/**
 * @union   data32_u
 * @brief   32bit共用体
 *
 * @typedef DATA32_U
 * @brief   32bit共用体
 */
typedef union data32_u {
    int32_t _s32;                   /*!< 符号あり，32bit */
    uint32_t _u32;                  /*!< 符号なし，32bit */
    int16_t _s16[2];                /*!< 符号あり，16bit */
    uint16_t _u16[2];               /*!< 符号なし，16bit */
    int8_t _s8[4];                  /*!< 符号あり，8bit */
    uint8_t _u8[4];                 /*!< 符号なし，8bit */
} DATA32_U;


/**
 * @brief   コマンドインタフェースを開く
 * @param[in,out]   cmdIF           コマンドインタフェース情報構造体
 * @param[in]       comName         シリアルポート名
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_open(COMMANDIF_T *cmdIF, LPCTSTR comName);


/**
 * @brief   コマンドインタフェースを閉じる
 * @param[in,out]   cmdIF           コマンドインタフェース情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_close(COMMANDIF_T *cmdIF);


/**
 * @brief   ソフトウェアリセットコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_ResetDevice(COMMANDIF_T *cmdIF);


/**
 * @brief   システム初期化コマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_InitializeSystem(COMMANDIF_T *cmdIF);


/**
 * @brief   バージョン情報取得コマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_GetVersion(COMMANDIF_T *cmdIF);


/**
 * @brief   レジスタ読込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 * @param[out]      readBytes       読込みバイト数
 * @retuen          レジスタ読込みデータ格納先のポインタ
 */
LPBYTE CommandIF_execCommand_ReadRegister(COMMANDIF_T *cmdIF, DWORD registerIndex, LPDWORD readBytes);


/**
 * @brief   レジスタ書込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 * @param[in]       data            レジスタ書込みデータ格納先のポインタ
 * @param[in]       dataBytes       レジスタ書込みデータのバイト数
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_WriteRegister(COMMANDIF_T *cmdIF, DWORD registerIndex, LPVOID data, DWORD dataBytes);


/**
 * @brief   EEPROM読込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 * @param[out]      readBytes       読込みバイト数
 * @retuen          EEPROM読込みデータ格納先のポインタ
 */
LPBYTE CommandIF_execCommand_ReadEEPROM(COMMANDIF_T *cmdIF, DWORD eepromIndex, LPDWORD readBytes);


/**
 * @brief   EEPROM書込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 * @param[in]       data            EEPROM書込みデータ格納先のポインタ
 * @param[in]       dataSize        EEPROM書込みデータのバイト数
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_WriteEEPROM(COMMANDIF_T *cmdIF, DWORD eepromIndex, LPVOID data, DWORD dataBytes);

#endif	/* __CAMERAMOUNT_COMMANDIF_H__ */
