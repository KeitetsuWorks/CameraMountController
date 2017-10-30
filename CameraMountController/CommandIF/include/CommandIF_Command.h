/**
 * @file        CommandIF_Command.h
 * @brief       コマンドインタフェース通信ライブラリ コマンド定義
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __COMMANDIF_COMMAND_H__
#define __COMMANDIF_COMMAND_H__


/**
 * @name    コマンドオペコード
 */
/*! @{ */
#define COMMAND_RESET                   0x0     /*!< オペコード: ソフトウェアリセット */
#define COMMAND_INITIALIZE              0x1     /*!< オペコード: システム初期化 */
#define COMMAND_GET_VERSION             0x2     /*!< オペコード: バージョン情報取得 */
#define COMMAND_READ_REGISTER           0x4     /*!< オペコード: レジスタ読込み */
#define COMMAND_WRITE_REGISTER          0x5     /*!< オペコード: レジスタ書込み */
#define COMMAND_READ_EEPROM             0x6     /*!< オペコード: EEPROM読込み */
#define COMMAND_WRITE_EEPROM            0x7     /*!< オペコード: EEPROM書込み */
/*! @} */


/**
 * @name    コマンドフォーマット
 */
/*! @{ */
#define COMMAND_LENGTH_MAX              6       /*!< 最大コマンド長 */
#define COMMAND_OPCODE_LENGTH           1       /*!< オペコード長 */
#define COMMAND_OPERAND_LENGTH_MAX      5       /*!< 最大オペランド長 */
/*! @} */


/**
 * @name    コマンドレスポンスフォーマット
 */
/*! @{ */
#define RESPONSE_LENGTH_MAX             6       /*!< 最大レスポンス長 */
#define RESPONSE_MASK_COMMAND_RESULT    0xF0    /*!< レスポンスマスク: コマンド実行結果 */
#define RESPONSE_MASK_LENGTH            0x0F    /*!< レスポンスマスク: レスポンス長 */
/*! @} */

#endif  /* __CAMERAMOUNT_COMMAND_H__ */
