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
/** @{ */
#define COMMAND_LENGTH_MAX              6       /**< 最大コマンド長 */
/** @} */


/**
 * @name    コマンドレスポンスフォーマット
 */
/** @{ */
#define RESPONSE_LENGTH_MAX             6       /**< 最大レスポンス長 */
/** @} */


/**
 * @struct  CommandIF_st
 * @brief   コマンドインタフェース情報構造体
 *
 * @typedef COMMANDIF_T
 * @brief   コマンドインタフェース情報構造体
 *
 * @typedef COMMANDIF
 * @brief   コマンドインタフェース情報構造体のポインタ
 */
typedef struct CommandIF_st {
    COMPORT comPort;                /**< シリアルポート情報構造体のポインタ */
    BYTE deviceType;                /**< デバイスタイプ */
    BYTE deviceVersion;             /**< デバイスバージョン */
    BYTE deviceRevision;            /**< デバイスリビジョン */
} COMMANDIF_T, *COMMANDIF;


/**
 * @union   data32_u
 * @brief   32bit共用体
 *
 * @typedef DATA32_U
 * @brief   32bit共用体
 */
typedef union data32_u {
    int32_t _s32;                   /**< 符号あり，32bit */
    uint32_t _u32;                  /**< 符号なし，32bit */
    int16_t _s16[2];                /**< 符号あり，16bit */
    uint16_t _u16[2];               /**< 符号なし，16bit */
    int8_t _s8[4];                  /**< 符号あり，8bit */
    uint8_t _u8[4];                 /**< 符号なし，8bit */
} DATA32_U;


/**
 * @brief   コマンドインタフェースを開く
 * @param[in]       comName         シリアルポート名
 * @retval          NULL            異常終了
 * @retval          Others          コマンドインタフェース情報構造体のポインタ
 */
COMMANDIF CommandIF_open(LPCTSTR comName);


/**
 * @brief   コマンドインタフェースを閉じる
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @retval          NULL            正常終了
 * @retval          Others          異常終了
 */
COMMANDIF CommandIF_close(COMMANDIF cmdIF);


/**
 * @brief   ソフトウェアリセットコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_ResetDevice(COMMANDIF cmdIF);


/**
 * @brief   システム初期化コマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_InitializeSystem(COMMANDIF cmdIF);


/**
 * @brief   バージョン情報取得コマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_GetVersion(COMMANDIF cmdIF);


/**
 * @brief   レジスタ読込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @param[in]       registerIndex   レジスタインデックス
 * @param[out]      readBytes       読込みバイト数
 * @return          レジスタ読込みデータ格納先のポインタ
 */
LPBYTE CommandIF_execCommand_ReadRegister(COMMANDIF cmdIF, DWORD registerIndex, LPDWORD readBytes);


/**
 * @brief   レジスタ書込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @param[in]       registerIndex   レジスタインデックス
 * @param[in]       data            レジスタ書込みデータ格納先のポインタ
 * @param[in]       dataBytes       レジスタ書込みデータのバイト数
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_WriteRegister(COMMANDIF cmdIF, DWORD registerIndex, LPVOID data, DWORD dataBytes);


/**
 * @brief   EEPROM読込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @param[in]       eepromIndex     EEPROMインデックス
 * @param[out]      readBytes       読込みバイト数
 * @return          EEPROM読込みデータ格納先のポインタ
 */
LPBYTE CommandIF_execCommand_ReadEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPDWORD readBytes);


/**
 * @brief   EEPROM書込みコマンドを実行する
 * @param[in]       cmdIF           コマンドインタフェース情報構造体のポインタ
 * @param[in]       eepromIndex     EEPROMインデックス
 * @param[in]       data            EEPROM書込みデータ格納先のポインタ
 * @param[in]       dataBytes       EEPROM書込みデータのバイト数
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CommandIF_execCommand_WriteEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPVOID data, DWORD dataBytes);

#endif	/* __CAMERAMOUNT_COMMANDIF_H__ */
