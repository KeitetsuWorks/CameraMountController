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


CAMERAMOUNT CameraMount_open(LPCTSTR comName)
{
    CAMERAMOUNT cameraMount;

    /* �C���X�^���X�̐��� */
    cameraMount = (CAMERAMOUNT)malloc(sizeof(CAMERAMOUNT_T));
    if (cameraMount == NULL) {
        _tprintf(_T("�J�����}�E���g�R���g���[���̃C���X�^���X�̐����Ɏ��s���܂���\n"));
        return NULL;
    }
    ZeroMemory(cameraMount, sizeof(CAMERAMOUNT_T));

    /* �R�}���h�C���^�t�F�[�X���J�� */
    cameraMount->cmdIF = CommandIF_open(comName);
    _tprintf(_T("�J�����}�E���g�R���g���[���̐ڑ���"));
    if (cameraMount->cmdIF != NULL) {
        _tprintf(_T("�������܂���\n"));
    }
    else {
        _tprintf(_T("���s���܂���\n"));
        free(cameraMount);
        return NULL;
    }

    return cameraMount;
}


CAMERAMOUNT CameraMount_close(CAMERAMOUNT cameraMount)
{
    _tprintf(_T("�J�����}�E���g�R���g���[���̐ؒf��"));
    if (cameraMount != NULL) {
        CommandIF_close(cameraMount->cmdIF);
        free(cameraMount);
        cameraMount = NULL;
        _tprintf(_T("�������܂���"));
    }
    else {
        _tprintf(_T("���s���܂���"));
    }
    _tprintf(_T("\n"));

    return cameraMount;
}


BOOL CameraMount_reset(CAMERAMOUNT cameraMount)
{
    return CommandIF_execCommand_ResetDevice(cameraMount->cmdIF);
}


BOOL CameraMount_initialize(CAMERAMOUNT cameraMount)
{
    return CommandIF_execCommand_InitializeSystem(cameraMount->cmdIF);
}


VOID CameraMount_printVersion(CAMERAMOUNT cameraMount)
{
    BOOL retval;

    retval = CommandIF_execCommand_GetVersion(cameraMount->cmdIF);
    if (retval != FALSE) {
        _tprintf(_T("�f�o�C�X�^�C�v: 0x%02x, �o�[�W����: %d.%d\n"),
            cameraMount->cmdIF->deviceType,
            cameraMount->cmdIF->deviceVersion,
            cameraMount->cmdIF->deviceRevision
        );
    }
    else {
        _tprintf(_T("�o�[�W�������̎擾�Ɏ��s���܂���\n"));
    }

    return;
}


BOOL CameraMount_validateVersion(CAMERAMOUNT cameraMount)
{
    BOOL retval;
    BOOL result;

    result = TRUE;

    retval = CommandIF_execCommand_GetVersion(cameraMount->cmdIF);
    if (retval != FALSE) {
        if ((cameraMount->cmdIF->deviceType != CAMERAMOUNT_SUPPORTED_TYPE)
            || (cameraMount->cmdIF->deviceVersion != CAMERAMOUNT_SUPPORTED_VERSION)
            || (cameraMount->cmdIF->deviceRevision != CAMERAMOUNT_SUPPORTED_REVISION)) {
            result = FALSE;
        }
    }
    else {
        result = FALSE;
    }

    return result;
}
