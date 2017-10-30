/**
 * @file        CommandIF_Command.h
 * @brief       �R�}���h�C���^�t�F�[�X�ʐM���C�u���� �R�}���h��`
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __COMMANDIF_COMMAND_H__
#define __COMMANDIF_COMMAND_H__


/**
 * @name    �R�}���h�I�y�R�[�h
 */
/*! @{ */
#define COMMAND_RESET                   0x0     /*!< �I�y�R�[�h: �\�t�g�E�F�A���Z�b�g */
#define COMMAND_INITIALIZE              0x1     /*!< �I�y�R�[�h: �V�X�e�������� */
#define COMMAND_GET_VERSION             0x2     /*!< �I�y�R�[�h: �o�[�W�������擾 */
#define COMMAND_READ_REGISTER           0x4     /*!< �I�y�R�[�h: ���W�X�^�Ǎ��� */
#define COMMAND_WRITE_REGISTER          0x5     /*!< �I�y�R�[�h: ���W�X�^������ */
#define COMMAND_READ_EEPROM             0x6     /*!< �I�y�R�[�h: EEPROM�Ǎ��� */
#define COMMAND_WRITE_EEPROM            0x7     /*!< �I�y�R�[�h: EEPROM������ */
/*! @} */


/**
 * @name    �R�}���h�t�H�[�}�b�g
 */
/*! @{ */
#define COMMAND_LENGTH_MAX              6       /*!< �ő�R�}���h�� */
#define COMMAND_OPCODE_LENGTH           1       /*!< �I�y�R�[�h�� */
#define COMMAND_OPERAND_LENGTH_MAX      5       /*!< �ő�I�y�����h�� */
/*! @} */


/**
 * @name    �R�}���h���X�|���X�t�H�[�}�b�g
 */
/*! @{ */
#define RESPONSE_LENGTH_MAX             6       /*!< �ő僌�X�|���X�� */
#define RESPONSE_MASK_COMMAND_RESULT    0xF0    /*!< ���X�|���X�}�X�N: �R�}���h���s���� */
#define RESPONSE_MASK_LENGTH            0x0F    /*!< ���X�|���X�}�X�N: ���X�|���X�� */
/*! @} */

#endif  /* __CAMERAMOUNT_COMMAND_H__ */
