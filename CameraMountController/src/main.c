/**
 * @file        main.c
 * @brief       �J�����}�E���g�R���g���[��
 * @author      Keitetsu
 * @date        2017/08/07
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <tchar.h>

#include "CameraMount.h"
#include "CameraMount_Register.h"
#include "CameraMount_EEPROM.h"


/**
 * @name    �ݒ�t�@�C��
 */
/*! @{ */
#define INI_FILE_NAME               "config.ini"        /*!< �ݒ�t�@�C���� */
#define INI_COMPORT_SECTION         "ComPort"           /*!< �V���A���|�[�g�Z�N�V���� */
#define INI_COMPORT_KEY_COMNAME     "ComName"           /*!< �V���A���|�[�g���L�[ */
/*! @} */

#define COMNAME_BUF_SIZE            16                  /*!< �V���A���|�[�g���o�b�t�@�̃T�C�Y */

LPCTSTR iniFileName = _T(INI_FILE_NAME);                /*!< �ݒ�t�@�C���� */
LPCTSTR comNameDefault = _T("\\\\.\\COM1");             /*!< ����̃V���A���|�[�g�� */

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR iniPath[MAX_PATH];
    TCHAR comName[COMNAME_BUF_SIZE];
    CAMERAMOUNT_T cameraMount;
    BOOL supportedVersion;

    /* ���P�[���̐ݒ� */
    _tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

    /* �ݒ�t�@�C���̃p�X���擾 */
    GetCurrentDirectory(MAX_PATH, iniPath);
    _tcscat_s(iniPath, MAX_PATH, _T("\\"));
    _tcscat_s(iniPath, MAX_PATH, iniFileName);

    /* �ݒ�t�@�C������V���A���|�[�g�����擾 */
    GetPrivateProfileString(
        _T(INI_COMPORT_SECTION),
        _T(INI_COMPORT_KEY_COMNAME),
        comNameDefault,
        comName,
        COMNAME_BUF_SIZE,
        iniPath
    );

    if(CameraMount_open(&cameraMount, comName) != TRUE){
        exit(EXIT_FAILURE);
    }

    CameraMount_printVersion(&cameraMount);
    supportedVersion = CameraMount_validateVersion(&cameraMount);
    if (supportedVersion == TRUE) {
        _tprintf(_T("�Ή��o�[�W�����ł�\n"));
    }
    else {
        _tprintf(_T("���Ή��o�[�W�����ł�\n"));
        exit(EXIT_FAILURE);
    }

    CameraMount_printAllRegister(&cameraMount);
    CameraMount_printAllEEPROM(&cameraMount);

    CameraMount_close(&cameraMount);

    exit(EXIT_SUCCESS);
}
