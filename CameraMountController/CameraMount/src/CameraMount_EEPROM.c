/**
 * @file        CameraMount_EEPROM.c
 * @brief       カメラマウントコントローラ EEPROMインタフェース
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
#include "CameraMount_EEPROM.h"


 /**
  * @var     EEPROM_table
  * @brief   レジスタテーブル
  */
static EEPROM_T EEPROM_table[] = {
    { _T(EEPROM_LABEL_SERVO_INITIAL_CTRL_MODE),             EEPROM_SIZE_SERVO_INITIAL_CTRL_MODE,                FALSE,  TRUE },
    { _T(EEPROM_LABEL_SERVO_POSITION_FACTOR),               EEPROM_SIZE_SERVO_POSITION_FACTOR,                  FALSE,  TRUE },
    { _T(EEPROM_LABEL_PAN_SERVO_INITIAL_ANGLE),             EEPROM_SIZE_PAN_SERVO_INITIAL_ANGLE,                FALSE,  TRUE },
    { _T(EEPROM_LABEL_PAN_SERVO_NEUTRAL_POSITION),          EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION,             FALSE,  TRUE },
    { _T(EEPROM_LABEL_PAN_SERVO_MIN_POSITION),              EEPROM_SIZE_PAN_SERVO_MIN_POSITION,                 FALSE,  TRUE },
    { _T(EEPROM_LABEL_PAN_SERVO_MAX_POSITION),              EEPROM_SIZE_PAN_SERVO_MAX_POSITION,                 FALSE,  TRUE },
    { _T(EEPROM_LABEL_TILT_SERVO_INITIAL_ANGLE),            EEPROM_SIZE_TILT_SERVO_INITIAL_ANGLE,               FALSE,  TRUE },
    { _T(EEPROM_LABEL_TILT_SERVO_NEUTRAL_POSITION),         EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION,            FALSE,  TRUE },
    { _T(EEPROM_LABEL_TILT_SERVO_MIN_POSITION),             EEPROM_SIZE_TILT_SERVO_MIN_POSITION,                FALSE,  TRUE },
    { _T(EEPROM_LABEL_TILT_SERVO_MAX_POSITION),             EEPROM_SIZE_TILT_SERVO_MAX_POSITION,                FALSE,  TRUE },
    { _T(EEPROM_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT), EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,    FALSE,  TRUE },
    { _T(EEPROM_LABEL_ERROR_LED_BRINK_PERIOD),              EEPROM_SIZE_ERROR_LED_BRINK_PERIOD,                 FALSE,  TRUE },
    { _T(EEPROM_LABEL_COM_TIMEOUT_LIMIT),                   EEPROM_SIZE_COM_TIMEOUT_LIMIT,                      FALSE,  TRUE }
};


BOOL CameraMount_eepromExists(DWORD eepromIndex)
{
    BOOL result;

    result = FALSE;

    if ((eepromIndex >= 0) && (eepromIndex < EEPROM_INDEX_NUM)) {
        result = TRUE;
    }

    return result;
}


DWORD CameraMount_getEEPROMSize(DWORD eepromIndex)
{
    DWORD size;
    BOOL retval;

    size = 0;

    retval = CameraMount_eepromExists(eepromIndex);
    if (retval != FALSE) {
        size = EEPROM_table[eepromIndex].size;
    }

    return size;
}


LPVOID CameraMount_readEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex)
{
    DWORD eepromSize;
    DWORD readBytes;
    LPVOID result;

    result = NULL;

    /* EEPROMデータサイズを取得 */
    eepromSize = CameraMount_getEEPROMSize(eepromIndex);

    /* EEPROM読込みを実行 */
    if (eepromSize > 0) {
        result = (LPVOID)CommandIF_execCommand_ReadEEPROM(&(cameraMount->cmdIF), eepromIndex, &readBytes);
        if (readBytes != eepromSize) {
            free(result);
            result = NULL;
        }
    }

    return result;
}


BOOL CameraMount_writeEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex, LPVOID data)
{
    DWORD eepromSize;
    BOOL result;

    result = TRUE;

    /* EEPROMデータサイズを取得 */
    eepromSize = CameraMount_getEEPROMSize(eepromIndex);

    /* EEPORM書込みを実行 */
    if (eepromSize > 0) {
        result = CommandIF_execCommand_WriteEEPROM(&(cameraMount->cmdIF), eepromIndex, data, eepromSize);
    }
    else {
        result = FALSE;
    }

    return result;
}


VOID CameraMount_printEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex)
{
    DATA32_U *eepromData;

    eepromData = (DATA32_U *)CameraMount_readEEPROM(cameraMount, eepromIndex);
    _tprintf(_T("[E:0x%02x] "), eepromIndex);
    if (eepromData != NULL) {
        /* EEPROMデータを表示 */
        switch (EEPROM_table[eepromIndex].size) {
        case 1:
            _tprintf(_T("0x%08x"), eepromData->_u8[0]);
            break;
        case 2:
            _tprintf(_T("0x%08x"), eepromData->_u16[0]);
            break;
        case 4:
            _tprintf(_T("0x%08x"), eepromData->_u32);
            break;
        default:
            _tprintf(_T("未対応のEEPROMデータサイズです"));
            break;
        }

        /* EEPROMデータサイズを表示 */
        _tprintf(_T(", %d Byte"), EEPROM_table[eepromIndex].size);

        /* 符号有無を表示 */
        if (EEPROM_table[eepromIndex].sign != FALSE) {
            _tprintf(_T(", S"));
        }
        else {
            _tprintf(_T(", U"));
        }

        /* 書込み可否を表示 */
        if (EEPROM_table[eepromIndex].write_enable != FALSE) {
            _tprintf(_T(", W/R"));
        }
        else {
            _tprintf(_T(", -/R"));
        }

        /* EEPROMラベルを表示 */
        _tprintf(_T(": %s"), EEPROM_table[eepromIndex].label);

        free(eepromData);
    }
    else {
        _tprintf(_T("EEPROM読込みに失敗しました"));
    }
    _tprintf(_T("\n"));

    return;
}


VOID CameraMount_printAllEEPROM(CAMERAMOUNT_T *cameraMount)
{
    DWORD eepromIndex;

    for (eepromIndex = 0; eepromIndex < EEPROM_INDEX_NUM; eepromIndex++) {
        CameraMount_printEEPROM(cameraMount, eepromIndex);
    }

    return;
}


BOOL CameraMount_editEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex)
{
    DATA32_U data;
    DWORD numberOfFields;
    BOOL retval;
    BOOL result;

    data._s32 = 0;
    numberOfFields = 0;
    result = TRUE;

    _tprintf(_T("[E:0x%02x] "), eepromIndex);
    if (EEPROM_table[eepromIndex].write_enable != FALSE) {
        /* EEPROM書込み処理 */
        switch (EEPROM_table[eepromIndex].size) {
        case 1:
            if (EEPROM_table[eepromIndex].sign != FALSE) {
                _tprintf(_T("新しい値 (符号あり10進数): "));
                numberOfFields = _tscanf_s(_T("%d"), &(data._s32));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): "));
                numberOfFields = _tscanf_s(_T("%u"), &(data._u32));
            }
            break;
        case 2:
            if (EEPROM_table[eepromIndex].sign != FALSE) {
                _tprintf(_T("新しい値 (符号あり10進数): "));
                numberOfFields = _tscanf_s(_T("%hd"), &(data._s16[0]));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): "));
                numberOfFields = _tscanf_s(_T("%hu"), &(data._u16[0]));
            }
            break;
        case 4:
            if (EEPROM_table[eepromIndex].sign != FALSE) {
                _tprintf(_T("新しい値 (符号あり10進数): "));
                numberOfFields = _tscanf_s(_T("%d"), &(data._s32));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): "));
                numberOfFields = _tscanf_s(_T("%u"), &(data._u32));
            }
            break;
        default:
            _tprintf(_T("未対応のEEPROMデータサイズです\n"));
            break;
        }

        if (numberOfFields == 1) {
            retval = CameraMount_writeEEPROM(cameraMount, eepromIndex, &data);
            if (retval != FALSE) {
                _tprintf(_T("書込みが成功しました\n"));
            }
            else {
                _tprintf(_T("書込みが失敗しました\n"));
                result = FALSE;
            }
        }
        else {
            _tprintf(_T("不正な値です\n"));
            result = FALSE;
        }
    }
    else {
        _tprintf(_T("書込みが禁止されています\n"));
        result = FALSE;
    }

    return result;
}
