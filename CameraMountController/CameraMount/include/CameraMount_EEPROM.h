/**
 * @file        CameraMount_EEPROM.h
 * @brief       カメラマウントコントローラ EEPROMインタフェース
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_EEPROM_H__
#define __CAMERAMOUNT_EEPROM_H__


/**
 * @name    EEPROMラベル
 */
 /*! @{ */
#define EEPROM_LABEL_SERVO_INITIAL_CTRL_MODE                    "サーボ制御モード，初期モード"
#define EEPROM_LABEL_SERVO_POSITION_FACTOR                      "サーボ角度位置変換係数"
#define EEPROM_LABEL_PAN_SERVO_INITIAL_ANGLE                    "水平方向用サーボ，初期角度"
#define EEPROM_LABEL_PAN_SERVO_NEUTRAL_POSITION                 "水平方向用サーボ，ニュートラル位置"
#define EEPROM_LABEL_PAN_SERVO_MIN_POSITION                     "水平方向用サーボ，最小位置"
#define EEPROM_LABEL_PAN_SERVO_MAX_POSITION                     "水平方向用サーボ，最大位置"
#define EEPROM_LABEL_TILT_SERVO_INITIAL_ANGLE                   "垂直方向用サーボ，初期角度"
#define EEPROM_LABEL_TILT_SERVO_NEUTRAL_POSITION                "垂直方向用サーボ，ニュートラル位置"
#define EEPROM_LABEL_TILT_SERVO_MIN_POSITION                    "垂直方向用サーボ，最小位置"
#define EEPROM_LABEL_TILT_SERVO_MAX_POSITION                    "垂直方向用サーボ，最大位置"
#define EEPROM_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT        "ステータスLEDの点滅周期，通信タイムアウト"
#define EEPROM_LABEL_ERROR_LED_BRINK_PERIOD                     "エラーLEDの点滅周期"
#define EEPROM_LABEL_COM_TIMEOUT_LIMIT                          "通信タイムアウト検出時間"
 /*! @} */


/**
 * @name    EEPROMデータサイズ
 */
/*! @{ */
#define EEPROM_SIZE_MAX                                         4       /*!< 最大サイズ */
#define EEPROM_SIZE_SERVO_INITIAL_CTRL_MODE                     1       /*!< サーボ制御モード，初期モード */
#define EEPROM_SIZE_SERVO_POSITION_FACTOR                       1       /*!< サーボ角度位置変換係数 */
#define EEPROM_SIZE_PAN_SERVO_INITIAL_ANGLE                     2       /*!< 水平方向用サーボ，初期角度 */
#define EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION                  2       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_PAN_SERVO_MIN_POSITION                      2       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_SIZE_PAN_SERVO_MAX_POSITION                      2       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_SIZE_TILT_SERVO_INITIAL_ANGLE                    2       /*!< 垂直方向用サーボ，初期角度 */
#define EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION                 2       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_SIZE_TILT_SERVO_MIN_POSITION                     2       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_SIZE_TILT_SERVO_MAX_POSITION                     2       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         1       /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_SIZE_ERROR_LED_BRINK_PERIOD                      1       /*!< エラーLEDの点滅周期 */
#define EEPROM_SIZE_COM_TIMEOUT_LIMIT                           1       /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    EEPROMインデックス
 */
/*! @{ */
#define EEPROM_SERVO_INITIAL_CTRL_MODE                          0       /*!< サーボ制御モード，初期モード */
#define EEPROM_SERVO_POSITION_FACTOR                            1       /*!< サーボ角度位置変換係数 */
#define EEPROM_PAN_SERVO_INITIAL_ANGLE                          2       /*!< 水平方向用サーボ，初期角度 */
#define EEPROM_PAN_SERVO_NEUTRAL_POSITION                       3       /*!< 水平方向用サーボ，ニュートラル位置 */
#define EEPROM_PAN_SERVO_MIN_POSITION                           4       /*!< 水平方向用サーボ，最小位置 */
#define EEPROM_PAN_SERVO_MAX_POSITION                           5       /*!< 水平方向用サーボ，最大位置 */
#define EEPROM_TILT_SERVO_INITIAL_ANGLE                         6       /*!< 垂直方向用サーボ，初期角度 */
#define EEPROM_TILT_SERVO_NEUTRAL_POSITION                      7       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define EEPROM_TILT_SERVO_MIN_POSITION                          8       /*!< 垂直方向用サーボ，最小位置 */
#define EEPROM_TILT_SERVO_MAX_POSITION                          9       /*!< 垂直方向用サーボ，最大位置 */
#define EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT              10      /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define EEPROM_ERROR_LED_BRINK_PERIOD                           11      /*!< エラーLEDの点滅周期 */
#define EEPROM_COM_TIMEOUT_LIMIT                                12      /*!< 通信タイムアウト検出時間 */
#define EEPROM_INDEX_NUM                                        13      /*!< EEPROMインデックスの数 */
/*! @} */


/**
 * @struct  eeprom_st
 * @brief   EEPROM情報構造体
 *
 * @typedef EEPROM_T
 * @brief   EEPROM情報構造体
 */
typedef struct eeprom_st {
    LPCTSTR label;              /*!< EEPROMラベル */
    DWORD size;                 /*!< EEPROMデータサイズ */
    BOOL sign;                  /*!< EEPROMデータ符号 */
    BOOL write_enable;          /*!< EEPROMライトイネーブル */
} EEPROM_T;


/**
 * @brief   EEPROMの存在確認
 * @param[in]       eepromIndex     EEPROMインデックス
 * @retval          TRUE            EEPROMは存在する
 * @retval          FALSE           EEPROMは存在しない
 */
BOOL CameraMount_eepromExists(DWORD eepromIndex);


/**
 * @brief   EEPROMデータサイズ取得処理
 * @param[in]       eepromIndex     EEPROMインデックス
 * @return          EEPROMデータサイズ
 */
DWORD CameraMount_getEEPROMSize(DWORD eepromIndex);


/**
 * @brief   EEPROM読込み処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 * @return          EEPROM読込みデータ格納先のポインタ
 */
LPVOID CameraMount_readEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);


/**
 * @brief   EEPROM書込み処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 * @param[in]       data            EEPROM書込みデータ格納先のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_writeEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex, LPVOID data);


/**
 * @brief   EEPROMデータ表示処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 */
VOID CameraMount_printEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);


/**
 * @brief   全EEPROMデータ表示処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 */
VOID CameraMount_printAllEEPROM(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   レジスタデータ編集処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       eepromIndex     EEPROMインデックス
 */
BOOL CameraMount_editEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);

#endif  /* __CAMERAMOUNT_EEPROM_H__ */
