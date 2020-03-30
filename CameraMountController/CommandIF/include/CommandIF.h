/**
 * @file        CommandIF.h
 * @brief       �R�}���h�C���^�t�F�[�X�ʐM���C�u����
 * @author      Keitetsu
 * @date        2017/07/17
 * @copyright   Copyright (c) 2017 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_COMMANDIF_H__
#define __CAMERAMOUNT_COMMANDIF_H__

#include <stdint.h>

#include "ComPort.h"


/**
 * @name    �R�}���h�t�H�[�}�b�g
 */
/** @{ */
#define COMMAND_LENGTH_MAX              6       /**< �ő�R�}���h�� */
/** @} */


/**
 * @name    �R�}���h���X�|���X�t�H�[�}�b�g
 */
/** @{ */
#define RESPONSE_LENGTH_MAX             6       /**< �ő僌�X�|���X�� */
/** @} */


/**
 * @struct  CommandIF_st
 * @brief   �R�}���h�C���^�t�F�[�X���\����
 *
 * @typedef COMMANDIF_T
 * @brief   �R�}���h�C���^�t�F�[�X���\����
 *
 * @typedef COMMANDIF
 * @brief   �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 */
typedef struct CommandIF_st {
    COMPORT comPort;                /**< �V���A���|�[�g���\���̂̃|�C���^ */
    BYTE deviceType;                /**< �f�o�C�X�^�C�v */
    BYTE deviceVersion;             /**< �f�o�C�X�o�[�W���� */
    BYTE deviceRevision;            /**< �f�o�C�X���r�W���� */
} COMMANDIF_T, *COMMANDIF;


/**
 * @union   data32_u
 * @brief   32bit���p��
 *
 * @typedef DATA32_U
 * @brief   32bit���p��
 */
typedef union data32_u {
    int32_t _s32;                   /**< ��������C32bit */
    uint32_t _u32;                  /**< �����Ȃ��C32bit */
    int16_t _s16[2];                /**< ��������C16bit */
    uint16_t _u16[2];               /**< �����Ȃ��C16bit */
    int8_t _s8[4];                  /**< ��������C8bit */
    uint8_t _u8[4];                 /**< �����Ȃ��C8bit */
} DATA32_U;


/**
 * @brief   �R�}���h�C���^�t�F�[�X���J��
 * @param[in]       comName         �V���A���|�[�g��
 * @retval          NULL            �ُ�I��
 * @retval          Others          �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 */
COMMANDIF CommandIF_open(LPCTSTR comName);


/**
 * @brief   �R�}���h�C���^�t�F�[�X�����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @retval          NULL            ����I��
 * @retval          Others          �ُ�I��
 */
COMMANDIF CommandIF_close(COMMANDIF cmdIF);


/**
 * @brief   �\�t�g�E�F�A���Z�b�g�R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CommandIF_execCommand_ResetDevice(COMMANDIF cmdIF);


/**
 * @brief   �V�X�e���������R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CommandIF_execCommand_InitializeSystem(COMMANDIF cmdIF);


/**
 * @brief   �o�[�W�������擾�R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CommandIF_execCommand_GetVersion(COMMANDIF cmdIF);


/**
 * @brief   ���W�X�^�Ǎ��݃R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @param[out]      readBytes       �Ǎ��݃o�C�g��
 * @return          ���W�X�^�Ǎ��݃f�[�^�i�[��̃|�C���^
 */
LPBYTE CommandIF_execCommand_ReadRegister(COMMANDIF cmdIF, DWORD registerIndex, LPDWORD readBytes);


/**
 * @brief   ���W�X�^�����݃R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @param[in]       data            ���W�X�^�����݃f�[�^�i�[��̃|�C���^
 * @param[in]       dataBytes       ���W�X�^�����݃f�[�^�̃o�C�g��
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CommandIF_execCommand_WriteRegister(COMMANDIF cmdIF, DWORD registerIndex, LPVOID data, DWORD dataBytes);


/**
 * @brief   EEPROM�Ǎ��݃R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @param[out]      readBytes       �Ǎ��݃o�C�g��
 * @return          EEPROM�Ǎ��݃f�[�^�i�[��̃|�C���^
 */
LPBYTE CommandIF_execCommand_ReadEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPDWORD readBytes);


/**
 * @brief   EEPROM�����݃R�}���h�����s����
 * @param[in]       cmdIF           �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @param[in]       data            EEPROM�����݃f�[�^�i�[��̃|�C���^
 * @param[in]       dataBytes       EEPROM�����݃f�[�^�̃o�C�g��
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CommandIF_execCommand_WriteEEPROM(COMMANDIF cmdIF, DWORD eepromIndex, LPVOID data, DWORD dataBytes);

#endif	/* __CAMERAMOUNT_COMMANDIF_H__ */
