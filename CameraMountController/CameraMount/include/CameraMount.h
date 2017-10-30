/**
 * @file        CameraMount.h
 * @brief       カメラマウントコントローラ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_H__
#define __CAMERAMOUNT_H__

#include "CommandIF.h"


/**
 * @name    カメラマウントコントローラ対応バージョン
 */
/*! @{ */
#define CAMERAMOUNT_SUPPORTED_TYPE          0x43        /*!< デバイスタイプ */
#define CAMERAMOUNT_SUPPORTED_VERSION       3           /*!< デバイスバージョン */
#define CAMERAMOUNT_SUPPORTED_REVISION      0           /*!< デバイスリビジョン */
/*! @} */


/**
 * @struct  CameraMount_st
 * @brief   カメラマウントコントローラ情報構造体
 *
 * @typedef CAMERAMOUNT_T
 * @brief   カメラマウントコントローラ情報構造体
 */
typedef struct CameraMount_st {
    COMMANDIF_T cmdIF;              /*!< コマンドインタフェース情報構造体 */
} CAMERAMOUNT_T;


/**
 * @brief   カメラマウントコントローラを開く
 * @param[in,out]   cameraMount     カメラマウントコントローラ情報構造体
 * @param[in]       comName         シリアルポート名
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_open(CAMERAMOUNT_T *cameraMount, LPCTSTR comName);


/**
 * @brief   カメラマウントコントローラを閉じる
 * @param[in,out]   cameraMount     カメラマウントコントローラ情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_close(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   カメラマウントコントローラをリセットする
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_reset(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   カメラマウントコントローラを初期化する
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_initialize(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   カメラマウントコントローラのバージョン情報表示処理
 * @param[in,out]   cameraMount     カメラマウントコントローラ情報構造体
 */
VOID CameraMount_printVersion(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   カメラマウントコントローラが対応バージョンか検証する
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体
 * @retval          TRUE            対応バージョン
 * @retval          FALSE           非対応バージョン
 */
BOOL CameraMount_validateVersion(CAMERAMOUNT_T *cameraMount);

#endif  /* __CAMERAMOUNT_H__ */
