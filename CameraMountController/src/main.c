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
/** @{ */
#define INI_FILE_NAME               "config.ini"        /**< 設定ファイル名 */
#define INI_COMPORT_SECTION         "ComPort"           /**< シリアルポートセクション */
#define INI_COMPORT_KEY_COMNAME     "ComName"           /**< シリアルポート名キー */
/** @} */

#define COMNAME_BUF_SIZE            16                  /**< シリアルポート名バッファのサイズ */
#define MENU_INPUT_BUF_SIZE         16                  /**< メニュー入力バッファのサイズ */


LPCTSTR iniFileName = _T(INI_FILE_NAME);                /**< 設定ファイル名 */
LPCTSTR comNameDefault = _T("\\\\.\\COM1");             /**< 既定のシリアルポート名 */


int _tmain(int argc, _TCHAR* argv[])
{
    TCHAR iniPath[MAX_PATH];
    TCHAR comName[COMNAME_BUF_SIZE];
    CAMERAMOUNT cameraMount;
    BOOL supportedVersion;
    BOOL flagExitMenu;
    TCHAR menuInputBuffer[MENU_INPUT_BUF_SIZE];
    DWORD numberOfFields;

    /* ロケールの設定 */
    _tsetlocale(LC_ALL, _T("Japanese_Japan.932"));

    /* 設定ファイルのパスを取得 */
    memset(iniPath, _T('\0'), MAX_PATH);
    GetCurrentDirectory(MAX_PATH, iniPath);
    _tcscat_s(iniPath, MAX_PATH, _T("\\"));
    _tcscat_s(iniPath, MAX_PATH, iniFileName);

    /* 設定ファイルからシリアルポート名を取得 */
    memset(comName, _T('\0'), COMNAME_BUF_SIZE);
    GetPrivateProfileString(
        _T(INI_COMPORT_SECTION),
        _T(INI_COMPORT_KEY_COMNAME),
        comNameDefault,
        comName,
        COMNAME_BUF_SIZE,
        iniPath
    );

    /* カメラマウントコントローラを接続しているシリアルポートを開く */
    cameraMount = CameraMount_open(comName);
    if (cameraMount == NULL) {
        exit(EXIT_FAILURE);
    }

    /* カメラマウントコントローラが対応バージョンか検証する */
    CameraMount_printVersion(cameraMount);
    supportedVersion = CameraMount_validateVersion(cameraMount);
    if (supportedVersion != FALSE) {
        _tprintf(_T("対応バージョンです\n"));
    }
    else {
        _tprintf(_T("非対応バージョンです\n"));

        CameraMount_close(cameraMount);

        exit(EXIT_FAILURE);
    }

    flagExitMenu = FALSE;
    while (flagExitMenu == FALSE) {
        memset(menuInputBuffer, _T('\0'), MENU_INPUT_BUF_SIZE);
        _tprintf(_T("--------------------------------\n"));
        _tprintf(_T("[c] リセット\n"));
        _tprintf(_T("[i] 初期化\n"));
        _tprintf(_T("[r] レジスタデータ表示\n"));
        _tprintf(_T("[w] レジスタデータ編集\n"));
        _tprintf(_T("[a] 全レジスタデータ表示\n"));
        _tprintf(_T("[e] EEPROMデータ表示\n"));
        _tprintf(_T("[f] EEPROMデータ編集\n"));
        _tprintf(_T("[g] 全EEPROMデータ表示\n"));
        _tprintf(_T("[q] 終了\n"));
        _tprintf(_T("操作を選択してください: "));
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
                _tprintf(_T("不正な操作です\n"));
                flagExitMenu = TRUE;
                break;
            }
        }
        else {
            _tprintf(_T("不正な操作です\n"));
            flagExitMenu = TRUE;
        }
        _tprintf(_T("\n"));
    }

    /* カメラマウントコントローラを接続しているシリアルポートを閉じる */
    CameraMount_close(cameraMount);

    exit(EXIT_SUCCESS);
}
