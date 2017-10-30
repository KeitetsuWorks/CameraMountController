/**
 * @file        main.c
 * @brief       カメラマウントコントローラ
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
 * @name    設定ファイル
 */
/*! @{ */
#define INI_FILE_NAME               "config.ini"        /*!< 設定ファイル名 */
#define INI_COMPORT_SECTION         "ComPort"           /*!< シリアルポートセクション */
#define INI_COMPORT_KEY_COMNAME     "ComName"           /*!< シリアルポート名キー */
/*! @} */

#define COMNAME_BUF_SIZE            16                  /*!< シリアルポート名バッファのサイズ */

LPCTSTR iniFileName = _T(INI_FILE_NAME);                /*!< 設定ファイル名 */
LPCTSTR comNameDefault = _T("\\\\.\\COM1");             /*!< 既定のシリアルポート名 */

int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR iniPath[MAX_PATH];
    TCHAR comName[COMNAME_BUF_SIZE];
    CAMERAMOUNT_T cameraMount;
    BOOL supportedVersion;

    /* ロケールの設定 */
    _tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

    /* 設定ファイルのパスを取得 */
    GetCurrentDirectory(MAX_PATH, iniPath);
    _tcscat_s(iniPath, MAX_PATH, _T("\\"));
    _tcscat_s(iniPath, MAX_PATH, iniFileName);

    /* 設定ファイルからシリアルポート名を取得 */
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
        _tprintf(_T("対応バージョンです\n"));
    }
    else {
        _tprintf(_T("未対応バージョンです\n"));
        exit(EXIT_FAILURE);
    }

    CameraMount_printAllRegister(&cameraMount);
    CameraMount_printAllEEPROM(&cameraMount);

    CameraMount_close(&cameraMount);

    exit(EXIT_SUCCESS);
}
