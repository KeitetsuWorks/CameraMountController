/**
 * @file        CameraMount.c
 * @brief       カメラマウントコントローラ
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <Windows.h>
#include <tchar.h>

#include "CommandIF.h"

#include "CameraMount.h"


BOOL CameraMount_open(CAMERAMOUNT_T *cameraMount, LPCTSTR comName)
{
    BOOL result;

    result = CommandIF_open(&(cameraMount->cmdIF), comName);
    _tprintf(_T("カメラマウントコントローラの接続に"));
    if (result != FALSE) {
        _tprintf(_T("成功しました"));
    }
    else {
        _tprintf(_T("失敗しました"));
    }
    _tprintf(_T("\n"));

    return result;
}


BOOL CameraMount_close(CAMERAMOUNT_T *cameraMount)
{
    BOOL result;

    result = CommandIF_close(&(cameraMount->cmdIF));
    _tprintf(_T("カメラマウントコントローラの切断に"));
    if (result != FALSE) {
        _tprintf(_T("成功しました"));
    }
    else {
        _tprintf(_T("失敗しました"));
    }
    _tprintf(_T("\n"));

    return result;
}


BOOL CameraMount_reset(CAMERAMOUNT_T *cameraMount)
{
    return CommandIF_execCommand_ResetDevice(&(cameraMount->cmdIF));
}


BOOL CameraMount_initialize(CAMERAMOUNT_T *cameraMount)
{
    return CommandIF_execCommand_InitializeSystem(&(cameraMount->cmdIF));
}


VOID CameraMount_printVersion(CAMERAMOUNT_T *cameraMount)
{
    BOOL retval;

    retval = CommandIF_execCommand_GetVersion(&(cameraMount->cmdIF));
    if (retval != FALSE) {
        _tprintf(_T("デバイスタイプ: 0x%02x, バージョン: %d.%d\n"),
            cameraMount->cmdIF.deviceType,
            cameraMount->cmdIF.deviceVersion,
            cameraMount->cmdIF.deviceRevision
        );
    }
    else {
        _tprintf(_T("バージョン情報の取得に失敗しました\n"));
    }

    return;
}


BOOL CameraMount_validateVersion(CAMERAMOUNT_T *cameraMount)
{
    BOOL retval;
    BOOL result;

    result = TRUE;

    retval = CommandIF_execCommand_GetVersion(&(cameraMount->cmdIF));
    if (retval != FALSE) {
        if ((cameraMount->cmdIF.deviceType != CAMERAMOUNT_SUPPORTED_TYPE)
            || (cameraMount->cmdIF.deviceVersion != CAMERAMOUNT_SUPPORTED_VERSION)
            || (cameraMount->cmdIF.deviceRevision != CAMERAMOUNT_SUPPORTED_REVISION)) {
            result = FALSE;
        }
    }
    else {
        result = FALSE;
    }

    return result;
}
