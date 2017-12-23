/**
 * @file        CameraMount_Register.c
 * @brief       �J�����}�E���g�R���g���[�� ���W�X�^�C���^�t�F�[�X
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
  * @brief   ���W�X�^�e�[�u��
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

    result = TRUE;

    if (registerIndex >= REGISTER_INDEX_NUM) {
        result = FALSE;
    }

    return result;
}


DWORD CameraMount_getRegisterSize(DWORD registerIndex)
{
    DWORD size;
    BOOL retval;

    size = 0;

    retval = CameraMount_registerExists(registerIndex);
    if (retval != FALSE) {
        size = Register_table[registerIndex].size;
    }

    return size;
}


LPVOID CameraMount_readRegister(CAMERAMOUNT cameraMount, DWORD registerIndex)
{
    DWORD registerSize;
    DWORD readBytes;
    LPVOID result;

    result = NULL;

    /* ���W�X�^�f�[�^�T�C�Y���擾 */
    registerSize = CameraMount_getRegisterSize(registerIndex);

    /* ���W�X�^�Ǎ��݂����s */
    if (registerSize > 0) {
        result = (LPVOID)CommandIF_execCommand_ReadRegister(cameraMount->cmdIF, registerIndex, &readBytes);
        if (readBytes != registerSize) {
            free(result);
            result = NULL;
        }
    }

    return result;
}


BOOL CameraMount_writeRegister(CAMERAMOUNT cameraMount, DWORD registerIndex, LPVOID data)
{
    DWORD registerSize;
    BOOL result;

    result = TRUE;

    /* ���W�X�^�f�[�^�T�C�Y���擾 */
    registerSize = CameraMount_getRegisterSize(registerIndex);

    /* ���W�X�^�����݂����s */
    if (registerSize > 0) {
        result = CommandIF_execCommand_WriteRegister(cameraMount->cmdIF, registerIndex, data, registerSize);
    }
    else {
        result = FALSE;
    }

    return result;
}


VOID CameraMount_printRegister_i(CAMERAMOUNT cameraMount, DWORD registerIndex)
{
    DATA32_U *registerData;

    registerData = (DATA32_U *)CameraMount_readRegister(cameraMount, registerIndex);
    _tprintf(_T("[R:0x%02x] "), registerIndex);
    if (registerData != NULL) {
        /* ���W�X�^�f�[�^��\�� */
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
            _tprintf(_T("���Ή��̃��W�X�^�f�[�^�T�C�Y�ł�"));
            break;
        }

        /* ���W�X�^�f�[�^�T�C�Y��\�� */
        _tprintf(_T(", %d Byte"), Register_table[registerIndex].size);

        /* �����L����\�� */
        if (Register_table[registerIndex].sign != FALSE) {
            _tprintf(_T(", S"));
        }
        else {
            _tprintf(_T(", U"));
        }

        /* �����݉ۂ�\�� */
        if (Register_table[registerIndex].write_enable != FALSE) {
            _tprintf(_T(", W/R"));
        }
        else {
            _tprintf(_T(", -/R"));
        }

        /* ���W�X�^���x����\�� */
        _tprintf(_T(": %s"), Register_table[registerIndex].label);

        free(registerData);
    }
    else {
        _tprintf(_T("���W�X�^�Ǎ��݂Ɏ��s���܂���"));
    }
    _tprintf(_T("\n"));

    return;
}


VOID CameraMount_printRegister(CAMERAMOUNT cameraMount)
{
    DWORD numberOfFields;
    DWORD registerIndex;
    BOOL retval;

    _tprintf(_T("�C���f�b�N�X: "));
    numberOfFields = _tscanf_s(_T("%u%*[^\n]"), &registerIndex);
    _tscanf_s(_T("%*c"));

    if (numberOfFields == 1) {
        retval = CameraMount_registerExists(registerIndex);
    }
    else {
        retval = FALSE;
    }

    if (retval == TRUE) {
        CameraMount_printRegister_i(cameraMount, registerIndex);
    }
    else {
        _tprintf(_T("�s���ȃC���f�b�N�X�ł�\n"));
    }

    return;
}


VOID CameraMount_printAllRegister(CAMERAMOUNT cameraMount)
{
    DWORD registerIndex;

    for (registerIndex = 0; registerIndex < REGISTER_INDEX_NUM; registerIndex++) {
        CameraMount_printRegister_i(cameraMount, registerIndex);
    }

    return;
}


BOOL CameraMount_editRegister_i(CAMERAMOUNT cameraMount, DWORD registerIndex)
{
    DATA32_U data;
    DWORD numberOfFields;
    BOOL retval;
    BOOL result;

    data._s32 = 0;
    numberOfFields = 0;
    result = TRUE;

    _tprintf(_T("[R:0x%02x] "), registerIndex);
    if (Register_table[registerIndex].write_enable != FALSE) {
        /* ���W�X�^�����ݏ��� */
        switch (Register_table[registerIndex].size) {
        case 1:
            if (Register_table[registerIndex].sign != FALSE) {
                _tprintf(_T("�V�����l (��������10�i��): "));
                numberOfFields = _tscanf_s(_T("%d%*[^\n]"), &(data._s32));
                _tscanf_s(_T("%*c"));
            }
            else {
                _tprintf(_T("�V�����l (�����Ȃ�10�i��): "));
                numberOfFields = _tscanf_s(_T("%u%*[^\n]"), &(data._u32));
                _tscanf_s(_T("%*c"));
            }
            break;
        case 2:
            if (Register_table[registerIndex].sign != FALSE) {
                _tprintf(_T("�V�����l (��������10�i��): "));
                numberOfFields = _tscanf_s(_T("%hd%*[^\n]"), &(data._s16[0]));
                _tscanf_s(_T("%*c"));
            }
            else {
                _tprintf(_T("�V�����l (�����Ȃ�10�i��): "));
                numberOfFields = _tscanf_s(_T("%hu%*[^\n]"), &(data._u16[0]));
                _tscanf_s(_T("%*c"));
            }
            break;
        case 4:
            if (Register_table[registerIndex].sign != FALSE) {
                _tprintf(_T("�V�����l (��������10�i��): "));
                numberOfFields = _tscanf_s(_T("%d%*[^\n]"), &(data._s32));
                _tscanf_s(_T("%*c"));
            }
            else {
                _tprintf(_T("�V�����l (�����Ȃ�10�i��): "));
                numberOfFields = _tscanf_s(_T("%u%*[^\n]"), &(data._u32));
                _tscanf_s(_T("%*c"));
            }
            break;
        default:
            _tprintf(_T("���Ή��̃��W�X�^�f�[�^�T�C�Y�ł�\n"));
            break;
        }

        if (numberOfFields == 1) {
            retval = CameraMount_writeRegister(cameraMount, registerIndex, &data);
            if (retval != FALSE) {
                _tprintf(_T("�����݂��������܂���\n"));
            }
            else {
                _tprintf(_T("�����݂����s���܂���\n"));
                result = FALSE;
            }
        }
        else {
            _tprintf(_T("�s���Ȓl�ł�\n"));
            result = FALSE;
        }
    }
    else {
        _tprintf(_T("�����݂��֎~����Ă��܂�\n"));
        result = FALSE;
    }

    return result;
}


BOOL CameraMount_editRegister(CAMERAMOUNT cameraMount)
{
    DWORD numberOfFields;
    DWORD registerIndex;
    BOOL retval;
    BOOL result;

    result = TRUE;

    _tprintf(_T("�C���f�b�N�X: "));
    numberOfFields = _tscanf_s(_T("%u%*[^\n]"), &registerIndex);
    _tscanf_s(_T("%*c"));

    if (numberOfFields == 1) {
        retval = CameraMount_registerExists(registerIndex);
    }
    else {
        retval = FALSE;
    }

    if (retval == TRUE) {
        result = CameraMount_editRegister_i(cameraMount, registerIndex);
    }
    else {
        _tprintf(_T("�s���ȃC���f�b�N�X�ł�\n"));
        result = FALSE;
    }

    return result;
}
