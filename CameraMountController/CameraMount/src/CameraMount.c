/**
 * @file        CameraMount.c
 * @brief       �J�����}�E���g�R���g���[��
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
    _tprintf(_T("�J�����}�E���g�R���g���[���̐ڑ���"));
    if (result != FALSE) {
        _tprintf(_T("�������܂���"));
    }
    else {
        _tprintf(_T("���s���܂���"));
    }
    _tprintf(_T("\n"));

    return result;
}


BOOL CameraMount_close(CAMERAMOUNT_T *cameraMount)
{
    BOOL result;

    result = CommandIF_close(&(cameraMount->cmdIF));
    _tprintf(_T("�J�����}�E���g�R���g���[���̐ؒf��"));
    if (result != FALSE) {
        _tprintf(_T("�������܂���"));
    }
    else {
        _tprintf(_T("���s���܂���"));
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
        _tprintf(_T("�f�o�C�X�^�C�v: 0x%02x, �o�[�W����: %d.%d\n"),
            cameraMount->cmdIF.deviceType,
            cameraMount->cmdIF.deviceVersion,
            cameraMount->cmdIF.deviceRevision
        );
    }
    else {
        _tprintf(_T("�o�[�W�������̎擾�Ɏ��s���܂���\n"));
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
