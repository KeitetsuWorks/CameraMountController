/**
 * @file        CameraMount_Register.c
 * @brief       カメラマウントコントローラ レジスタインタフェース
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
#include "CameraMount_Register.h"


 /**
  * @var     Register_table
  * @brief   レジスタテーブル
  */
static REGISTER_T Register_table[] = {
    { _T(REGISTER_LABEL_SYSTEM_STATE),                          REGISTER_SIZE_SYSTEM_STATE,                         FALSE,  FALSE },
    { _T(REGISTER_LABEL_SYSTEM_STATUS),                         REGISTER_SIZE_SYSTEM_STATUS,                        FALSE,  TRUE },
    { _T(REGISTER_LABEL_SYSTEM_ERROR),                          REGISTER_SIZE_SYSTEM_ERROR,                         FALSE,  TRUE },
    { _T(REGISTER_LABEL_SERVO_CTRL_MODE),                       REGISTER_SIZE_SERVO_CTRL_MODE,                      FALSE,  TRUE },
    { _T(REGISTER_LABEL_SERVO_POSITION_FACTOR),                 REGISTER_SIZE_SERVO_POSITION_FACTOR,                FALSE,  TRUE },
    { _T(REGISTER_LABEL_PAN_SERVO_REQUEST_ANGLE),               REGISTER_SIZE_PAN_SERVO_REQUEST_ANGLE,              TRUE,   TRUE },
    { _T(REGISTER_LABEL_PAN_SERVO_REQUEST_POSITION),            REGISTER_SIZE_PAN_SERVO_REQUEST_POSITION,           FALSE,  TRUE },
    { _T(REGISTER_LABEL_PAN_SERVO_NEUTRAL_POSITION),            REGISTER_SIZE_PAN_SERVO_NEUTRAL_POSITION,           FALSE,  TRUE },
    { _T(REGISTER_LABEL_PAN_SERVO_MIN_POSITION),                REGISTER_SIZE_PAN_SERVO_MIN_POSITION,               FALSE,  TRUE },
    { _T(REGISTER_LABEL_PAN_SERVO_MAX_POSITION),                REGISTER_SIZE_PAN_SERVO_MAX_POSITION,               FALSE,  TRUE },
    { _T(REGISTER_LABEL_TILT_SERVO_REQUEST_ANGLE),              REGISTER_SIZE_TILT_SERVO_REQUEST_ANGLE,             TRUE,   TRUE },
    { _T(REGISTER_LABEL_TILT_SERVO_REQUEST_POSITION),           REGISTER_SIZE_TILT_SERVO_REQUEST_POSITION,          FALSE,  TRUE },
    { _T(REGISTER_LABEL_TILT_SERVO_NEUTRAL_POSITION),           REGISTER_SIZE_TILT_SERVO_NEUTRAL_POSITION,          FALSE,  TRUE },
    { _T(REGISTER_LABEL_TILT_SERVO_MIN_POSITION),               REGISTER_SIZE_TILT_SERVO_MIN_POSITION,              FALSE,  TRUE },
    { _T(REGISTER_LABEL_TILT_SERVO_MAX_POSITION),               REGISTER_SIZE_TILT_SERVO_MAX_POSITION,              FALSE,  TRUE },
    { _T(REGISTER_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT),   REGISTER_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT,  FALSE,  TRUE },
    { _T(REGISTER_LABEL_ERROR_LED_BRINK_PERIOD),                REGISTER_SIZE_ERROR_LED_BRINK_PERIOD,               FALSE,  TRUE },
    { _T(REGISTER_LABEL_COM_TIMEOUT_LIMIT),                     REGISTER_SIZE_COM_TIMEOUT_LIMIT,                    FALSE,  TRUE }
};


BOOL CameraMount_registerExists(DWORD registerIndex)
{
    BOOL result;

    result = FALSE;

    if ((registerIndex >= 0) && (registerIndex < REGISTER_INDEX_NUM)) {
        result = TRUE;
    }

    return result;
}


DWORD CameraMount_getRegisterSize(DWORD registerIndex)
{
    DWORD size;
    BOOL retval;

    size = 0;

    retval = CameraMount_registerExists(registerIndex);
    if (retval == TRUE) {
        size = Register_table[registerIndex].size;
    }

    return size;
}


LPVOID CameraMount_readRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex)
{
    DWORD registerSize;
    DWORD readBytes;
    LPVOID result;

    result = NULL;

    /* レジスタデータサイズを取得 */
    registerSize = CameraMount_getRegisterSize(registerIndex);

    /* レジスタ読込みを実行 */
    if (registerSize > 0) {
        result = (LPVOID)CommandIF_execCommand_ReadRegister(&(cameraMount->cmdIF), registerIndex, &readBytes);
        if (readBytes != registerSize) {
            free(result);
            result = NULL;
        }
    }

    return result;
}


BOOL CameraMount_writeRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex, LPVOID data)
{
    DWORD registerSize;
    BOOL result;

    result = TRUE;

    /* レジスタデータサイズを取得 */
    registerSize = CameraMount_getRegisterSize(registerIndex);

    /* レジスタ書込みを実行 */
    if (registerSize > 0) {
        result = CommandIF_execCommand_WriteRegister(&(cameraMount->cmdIF), registerIndex, data, registerSize);
    }
    else {
        result = FALSE;
    }

    return result;
}


VOID CameraMount_printRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex)
{
    DATA32_U *registerData;

    registerData = (DATA32_U *)CameraMount_readRegister(cameraMount, registerIndex);
    _tprintf(_T("[R:0x%02x] "), registerIndex);
    if (registerData != NULL) {
        /* レジスタデータを表示 */
        switch (Register_table[registerIndex].size) {
        case 1:
            _tprintf(_T("0x%08x"), registerData->_u8[0]);
            break;
        case 2:
            _tprintf(_T("0x%08x"), registerData->_u16[0]);
            break;
        case 4:
            _tprintf(_T("0x%08x"), registerData->_u32);
            break;
        default:
            _tprintf(_T("未対応のレジスタデータサイズです"));
            break;
        }

        /* レジスタデータサイズを表示 */
        _tprintf(_T(", %d Byte"), Register_table[registerIndex].size);

        /* 符号有無を表示 */
        if (Register_table[registerIndex].sign == TRUE) {
            _tprintf(_T(", S"));
        }
        else {
            _tprintf(_T(", U"));
        }

        /* 書込み可否を表示 */
        if (Register_table[registerIndex].write_enable == TRUE) {
            _tprintf(_T(", W/R"));
        }
        else {
            _tprintf(_T(", -/R"));
        }

        /* レジスタラベルを表示 */
        _tprintf(_T(": %s"), Register_table[registerIndex].label);

        free(registerData);
    }
    else {
        _tprintf(_T("レジスタ読込みに失敗しました"));
    }
    _tprintf(_T("\n"));

    return;
}


VOID CameraMount_printAllRegister(CAMERAMOUNT_T *cameraMount)
{
    DWORD registerIndex;

    for (registerIndex = 0; registerIndex < REGISTER_INDEX_NUM; registerIndex++) {
        CameraMount_printRegister(cameraMount, registerIndex);
    }

    return;
}


BOOL CameraMount_editRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex)
{
    DATA32_U data;
    BOOL result;

    _tprintf(_T("[R:0x%02x] "), registerIndex);
    if (Register_table[registerIndex].write_enable == TRUE) {
        /* レジスタ書込み処理 */
        switch (Register_table[registerIndex].size) {
        case 1:
            if (Register_table[registerIndex].sign == TRUE) {
                _tprintf(_T("新しい値 (符号あり10進数): ")); _tscanf_s(_T("%d"), &(data._s32));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): ")); _tscanf_s(_T("%u"), &(data._u32));
            }
            break;
        case 2:
            if (Register_table[registerIndex].sign == TRUE) {
                _tprintf(_T("新しい値 (符号あり10進数): ")); _tscanf_s(_T("%hd"), &(data._s16[0]));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): ")); _tscanf_s(_T("%hu"), &(data._u16[0]));
            }
            break;
        case 4:
            if (Register_table[registerIndex].sign == TRUE) {
                _tprintf(_T("新しい値 (符号あり10進数): ")); _tscanf_s(_T("%d"), &(data._s32));
            }
            else {
                _tprintf(_T("新しい値 (符号なし10進数): ")); _tscanf_s(_T("%u"), &(data._u32));
            }
            break;
        default:
            _tprintf(_T("未対応のレジスタデータサイズです\n"));
            break;
        }
        result = CameraMount_writeRegister(cameraMount, registerIndex, &data);
        if (result == TRUE) {
            _tprintf(_T("書込みが成功しました\n"));
        }
        else {
            _tprintf(_T("書込みが失敗しました\n"));
        }
    }
    else {
        _tprintf(_T("書込みが禁止されています\n"));
        result = FALSE;
    }

    return result;
}
