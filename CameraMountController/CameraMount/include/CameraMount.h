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
 *
 * @typedef CAMERAMOUNT
 * @brief   カメラマウントコントローラ情報構造体のポインタ
 */
typedef struct CameraMount_st {
    COMMANDIF cmdIF;                /*!< コマンドインタフェース情報構造体のポインタ */
} CAMERAMOUNT_T, *CAMERAMOUNT;


/**
 * @brief   カメラマウントコントローラを開く
 * @param[in]       comName         シリアルポート名
 * @retval          NULL            異常終了
 * @retval          Others          カメラマウントコントローラ情報構造体のポインタ
 */
CAMERAMOUNT CameraMount_open(LPCTSTR comName);


/**
 * @brief   カメラマウントコントローラを閉じる
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体のポインタ
 * @retval          NULL            正常終了
 * @retval          Others          異常終了
 */
CAMERAMOUNT CameraMount_close(CAMERAMOUNT cameraMount);


/**
 * @brief   カメラマウントコントローラをリセットする
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_reset(CAMERAMOUNT cameraMount);


/**
 * @brief   カメラマウントコントローラを初期化する
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体のポインタ
 * @retval          TRUE            正常終了
 * @retval          FALSE           異常終了
 */
BOOL CameraMount_initialize(CAMERAMOUNT cameraMount);


/**
 * @brief   カメラマウントコントローラのバージョン情報表示処理
 * @param[in,out]   cameraMount     カメラマウントコントローラ情報構造体のポインタ
 */
VOID CameraMount_printVersion(CAMERAMOUNT cameraMount);


/**
 * @brief   カメラマウントコントローラが対応バージョンか検証する
 * @param[in]       cameraMount     カメラマウントコントローラ情報構造体のポインタ
 * @retval          TRUE            対応バージョン
 * @retval          FALSE           非対応バージョン
 */
BOOL CameraMount_validateVersion(CAMERAMOUNT cameraMount);

#endif  /* __CAMERAMOUNT_H__ */
