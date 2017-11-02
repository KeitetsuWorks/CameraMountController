/**
 * @file        CameraMount_Register.h
 * @brief       カメラマウントコントローラ レジスタインタフェース
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_REGISTER_H__
#define __CAMERAMOUNT_REGISTER_H__


/**
 * @name    レジスタラベル
 */
 /*! @{ */
#define REGISTER_LABEL_SYSTEM_STATE                             "システムステート"
#define REGISTER_LABEL_SYSTEM_STATUS                            "システムステータス"
#define REGISTER_LABEL_SYSTEM_ERROR                             "システムエラー"
#define REGISTER_LABEL_SERVO_CTRL_MODE                          "サーボ制御モード"
#define REGISTER_LABEL_SERVO_POSITION_FACTOR                    "サーボ角度位置変換係数"
#define REGISTER_LABEL_PAN_SERVO_REQUEST_ANGLE                  "水平方向用サーボ，指示角度"
#define REGISTER_LABEL_PAN_SERVO_REQUEST_POSITION               "水平方向用サーボ，指示位置"
#define REGISTER_LABEL_PAN_SERVO_NEUTRAL_POSITION               "水平方向用サーボ，ニュートラル位置"
#define REGISTER_LABEL_PAN_SERVO_MIN_POSITION                   "水平方向用サーボ，最小位置"
#define REGISTER_LABEL_PAN_SERVO_MAX_POSITION                   "水平方向用サーボ，最大位置"
#define REGISTER_LABEL_TILT_SERVO_REQUEST_ANGLE                 "垂直方向用サーボ，指示角度"
#define REGISTER_LABEL_TILT_SERVO_REQUEST_POSITION              "垂直方向用サーボ，指示位置"
#define REGISTER_LABEL_TILT_SERVO_NEUTRAL_POSITION              "垂直方向用サーボ，ニュートラル位置"
#define REGISTER_LABEL_TILT_SERVO_MIN_POSITION                  "垂直方向用サーボ，最小位置"
#define REGISTER_LABEL_TILT_SERVO_MAX_POSITION                  "垂直方向用サーボ，最大位置"
#define REGISTER_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT      "ステータスLEDの点滅周期，通信タイムアウト"
#define REGISTER_LABEL_ERROR_LED_BRINK_PERIOD                   "エラーLEDの点滅周期"
#define REGISTER_LABEL_COM_TIMEOUT_LIMIT                        "通信タイムアウト検出時間"
 /*! @} */


/**
 * @name    レジスタデータサイズ
 */
/*! @{ */
#define REGISTER_SIZE_SYSTEM_STATE                              1       /*!< システムステート */
#define REGISTER_SIZE_SYSTEM_STATUS                             1       /*!< システムステータス */
#define REGISTER_SIZE_SYSTEM_ERROR                              1       /*!< システムエラー */
#define REGISTER_SIZE_SERVO_CTRL_MODE                           1       /*!< サーボ制御モード */
#define REGISTER_SIZE_SERVO_POSITION_FACTOR                     1       /*!< サーボ角度位置変換係数 */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_ANGLE                   2       /*!< 水平方向用サーボ，指示角度 */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_POSITION                2       /*!< 水平方向用サーボ，指示位置 */
#define REGISTER_SIZE_PAN_SERVO_NEUTRAL_POSITION                2       /*!< 水平方向用サーボ，ニュートラル位置 */
#define REGISTER_SIZE_PAN_SERVO_MIN_POSITION                    2       /*!< 水平方向用サーボ，最小位置 */
#define REGISTER_SIZE_PAN_SERVO_MAX_POSITION                    2       /*!< 水平方向用サーボ，最大位置 */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_ANGLE                  2       /*!< 垂直方向用サーボ，指示角度 */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_POSITION               2       /*!< 垂直方向用サーボ，指示位置 */
#define REGISTER_SIZE_TILT_SERVO_NEUTRAL_POSITION               2       /*!< 垂直方向用サーボ，ニュートラル位置 */
#define REGISTER_SIZE_TILT_SERVO_MIN_POSITION                   2       /*!< 垂直方向用サーボ，最小位置 */
#define REGISTER_SIZE_TILT_SERVO_MAX_POSITION                   2       /*!< 垂直方向用サーボ，最大位置 */
#define REGISTER_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT       1       /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define REGISTER_SIZE_ERROR_LED_BRINK_PERIOD                    1       /*!< エラーLEDの点滅周期 */
#define REGISTER_SIZE_COM_TIMEOUT_LIMIT                         1       /*!< 通信タイムアウト検出時間 */
/*! @} */


/**
 * @name    レジスタインデックス
 */
/*! @{ */
#define REGISTER_SYSTEM_STATE                                   0       /*!< システムステート */
#define REGISTER_SYSTEM_STATUS                                  1       /*!< システムステータス */
#define REGISTER_SYSTEM_ERROR                                   2       /*!< システムエラー */
#define REGISTER_SERVO_CTRL_MODE                                3       /*!< サーボ制御モード */
#define REGISTER_SERVO_POSITION_FACTOR                          4       /*!< サーボ角度位置変換係数 */
#define REGISTER_PAN_SERVO_REQUEST_ANGLE                        5       /*!< 水平方向用サーボ，指示角度 */
#define REGISTER_PAN_SERVO_REQUEST_POSITION                     6       /*!< 水平方向用サーボ，指示位置 */
#define REGISTER_PAN_SERVO_NEUTRAL_POSITION                     7       /*!< 水平方向用サーボ，ニュートラル位置 */
#define REGISTER_PAN_SERVO_MIN_POSITION                         8       /*!< 水平方向用サーボ，最小位置 */
#define REGISTER_PAN_SERVO_MAX_POSITION                         9       /*!< 水平方向用サーボ，最大位置 */
#define REGISTER_TILT_SERVO_REQUEST_ANGLE                       10      /*!< 垂直方向用サーボ，指示角度 */
#define REGISTER_TILT_SERVO_REQUEST_POSITION                    11      /*!< 垂直方向用サーボ，指示位置 */
#define REGISTER_TILT_SERVO_NEUTRAL_POSITION                    12      /*!< 垂直方向用サーボ，ニュートラル位置 */
#define REGISTER_TILT_SERVO_MIN_POSITION                        13      /*!< 垂直方向用サーボ，最小位置 */
#define REGISTER_TILT_SERVO_MAX_POSITION                        14      /*!< 垂直方向用サーボ，最大位置 */
#define REGISTER_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT            15      /*!< ステータスLEDの点滅周期，通信タイムアウト */
#define REGISTER_ERROR_LED_BRINK_PERIOD                         16      /*!< エラーLEDの点滅周期 */
#define REGISTER_COM_TIMEOUT_LIMIT                              17      /*!< 通信タイムアウト検出時間 */
#define REGISTER_INDEX_NUM                                      18      /*!< レジスタインデックスの数 */
/*! @} */


/**
 * @struct  register_st
 * @brief   レジスタ情報構造体
 *
 * @typedef REGISTER_T
 * @brief   レジスタ情報構造体
 */
typedef struct register_st {
    LPCTSTR label;              /*!< レジスタラベル */
    DWORD size;                 /*!< レジスタデータサイズ */
    BOOL sign;                  /*!< レジスタデータ符号 */
    BOOL write_enable;          /*!< レジスタライトイネーブル */
} REGISTER_T;


/**
 * @brief   レジスタの存在確認
 * @param[in]       registerIndex   レジスタインデックス
 * @retval          TRUE            レジスタは存在する
 * @retval          FALSE           レジスタは存在しない
 */
BOOL CameraMount_registerExists(DWORD registerIndex);


/**
 * @brief   レジスタデータサイズ取得処理
 * @param[in]       registerIndex   レジスタインデックス
 * @return          レジスタデータサイズ
 */
DWORD CameraMount_getRegisterSize(DWORD registerIndex);


/**
 * @brief   レジスタ読込み処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 * @return          レジスタ読込みデータ格納先のポインタ
 */
LPVOID CameraMount_readRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   レジスタ書込み処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 * @param[in]       data            レジスタ書込みデータ格納先のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_writeRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex, LPVOID data);


/**
 * @brief   レジスタデータ表示処理（レジスタインデックス指定）
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 */
VOID CameraMount_printRegister_i(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   レジスタデータ表示処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 */
VOID CameraMount_printRegister(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   全レジスタデータ表示処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 */
VOID CameraMount_printAllRegister(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   レジスタデータ編集処理（レジスタインデックス指定）
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       registerIndex   レジスタインデックス
 */
BOOL CameraMount_editRegister_i(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   レジスタデータ編集処理
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 */
BOOL CameraMount_editRegister(CAMERAMOUNT_T *cameraMount);

#endif  /* __CAMERAMOUNT_REGISTER_H__ */
