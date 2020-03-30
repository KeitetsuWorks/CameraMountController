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
/** @{ */
#define INI_FILE_NAME               "config.ini"        /**< �ݒ�t�@�C���� */
#define INI_COMPORT_SECTION         "ComPort"           /**< �V���A���|�[�g�Z�N�V���� */
#define INI_COMPORT_KEY_COMNAME     "ComName"           /**< �V���A���|�[�g���L�[ */
/** @} */

#define COMNAME_BUF_SIZE            16                  /**< �V���A���|�[�g���o�b�t�@�̃T�C�Y */
#define MENU_INPUT_BUF_SIZE         16                  /**< ���j���[���̓o�b�t�@�̃T�C�Y */


LPCTSTR iniFileName = _T(INI_FILE_NAME);                /**< �ݒ�t�@�C���� */
LPCTSTR comNameDefault = _T("\\\\.\\COM1");             /**< ����̃V���A���|�[�g�� */


int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR iniPath[MAX_PATH];
    TCHAR comName[COMNAME_BUF_SIZE];
    CAMERAMOUNT cameraMount;
    BOOL supportedVersion;
    BOOL flagExitMenu;
    TCHAR menuInputBuffer[MENU_INPUT_BUF_SIZE];
    DWORD numberOfFields;

    /* ���P�[���̐ݒ� */
    _tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

    /* �ݒ�t�@�C���̃p�X���擾 */
    memset(iniPath, _T('\0'), MAX_PATH);
    GetCurrentDirectory(MAX_PATH, iniPath);
    _tcscat_s(iniPath, MAX_PATH, _T("\\"));
    _tcscat_s(iniPath, MAX_PATH, iniFileName);

    /* �ݒ�t�@�C������V���A���|�[�g�����擾 */
    memset(comName, _T('\0'), COMNAME_BUF_SIZE);
    GetPrivateProfileString(
        _T(INI_COMPORT_SECTION),
        _T(INI_COMPORT_KEY_COMNAME),
        comNameDefault,
        comName,
        COMNAME_BUF_SIZE,
        iniPath
    );

    /* �J�����}�E���g�R���g���[����ڑ����Ă���V���A���|�[�g���J�� */
    cameraMount = CameraMount_open(comName);
    if (cameraMount == NULL) {
        exit(EXIT_FAILURE);
    }

    /* �J�����}�E���g�R���g���[�����Ή��o�[�W���������؂��� */
    CameraMount_printVersion(cameraMount);
    supportedVersion = CameraMount_validateVersion(cameraMount);
    if (supportedVersion != FALSE) {
        _tprintf(_T("�Ή��o�[�W�����ł�\n"));
    }
    else {
        _tprintf(_T("��Ή��o�[�W�����ł�\n"));

        CameraMount_close(cameraMount);

        exit(EXIT_FAILURE);
    }

    flagExitMenu = FALSE;
    while (flagExitMenu == FALSE) {
        memset(menuInputBuffer, _T('\0'), MENU_INPUT_BUF_SIZE);
        _tprintf(_T("--------------------------------\n"));
        _tprintf(_T("[c] ���Z�b�g\n"));
        _tprintf(_T("[i] ������\n"));
        _tprintf(_T("[r] ���W�X�^�f�[�^�\��\n"));
        _tprintf(_T("[w] ���W�X�^�f�[�^�ҏW\n"));
        _tprintf(_T("[a] �S���W�X�^�f�[�^�\��\n"));
        _tprintf(_T("[e] EEPROM�f�[�^�\��\n"));
        _tprintf(_T("[f] EEPROM�f�[�^�ҏW\n"));
        _tprintf(_T("[g] �SEEPROM�f�[�^�\��\n"));
        _tprintf(_T("[q] �I��\n"));
        _tprintf(_T("�����I�����Ă�������: "));
        numberOfFields = _tscanf_s(_T("%15s%*[^\n]"), menuInputBuffer, MENU_INPUT_BUF_SIZE);
        _tscanf_s(_T("%*c"));

        if (numberOfFields == 1) {
            switch (menuInputBuffer[0]) {
            case _T('c'):
                CameraMount_reset(cameraMount);
                break;
            case _T('i'):
                CameraMount_initialize(cameraMount);
                break;
            case _T('r'):
                CameraMount_printRegister(cameraMount);
                break;
            case _T('w'):
                CameraMount_editRegister(cameraMount);
                break;
            case _T('a'):
                CameraMount_printAllRegister(cameraMount);
                break;
            case _T('e'):
                CameraMount_printEEPROM(cameraMount);
                break;
            case _T('f'):
                CameraMount_editEEPROM(cameraMount);
                break;
            case _T('g'):
                CameraMount_printAllEEPROM(cameraMount);
                break;
            case _T('q'):
                flagExitMenu = TRUE;
                break;
            default:
                _tprintf(_T("�s���ȑ���ł�\n"));
                flagExitMenu = TRUE;
                break;
            }
        }
        else {
            _tprintf(_T("�s���ȑ���ł�\n"));
            flagExitMenu = TRUE;
        }
        _tprintf(_T("\n"));
    }

    /* �J�����}�E���g�R���g���[����ڑ����Ă���V���A���|�[�g����� */
    CameraMount_close(cameraMount);

    exit(EXIT_SUCCESS);
}
