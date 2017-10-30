/**
 * @file        CameraMount_EEPROM.h
 * @brief       �J�����}�E���g�R���g���[�� EEPROM�C���^�t�F�[�X
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_EEPROM_H__
#define __CAMERAMOUNT_EEPROM_H__


/**
 * @name    EEPROM���x��
 */
 /*! @{ */
#define EEPROM_LABEL_SERVO_INITIAL_CTRL_MODE                    "�T�[�{���䃂�[�h�C�������[�h"
#define EEPROM_LABEL_SERVO_POSITION_FACTOR                      "�T�[�{�p�x�ʒu�ϊ��W��"
#define EEPROM_LABEL_PAN_SERVO_INITIAL_ANGLE                    "���������p�T�[�{�C�����p�x"
#define EEPROM_LABEL_PAN_SERVO_NEUTRAL_POSITION                 "���������p�T�[�{�C�j���[�g�����ʒu"
#define EEPROM_LABEL_PAN_SERVO_MIN_POSITION                     "���������p�T�[�{�C�ŏ��ʒu"
#define EEPROM_LABEL_PAN_SERVO_MAX_POSITION                     "���������p�T�[�{�C�ő�ʒu"
#define EEPROM_LABEL_TILT_SERVO_INITIAL_ANGLE                   "���������p�T�[�{�C�����p�x"
#define EEPROM_LABEL_TILT_SERVO_NEUTRAL_POSITION                "���������p�T�[�{�C�j���[�g�����ʒu"
#define EEPROM_LABEL_TILT_SERVO_MIN_POSITION                    "���������p�T�[�{�C�ŏ��ʒu"
#define EEPROM_LABEL_TILT_SERVO_MAX_POSITION                    "���������p�T�[�{�C�ő�ʒu"
#define EEPROM_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT        "�X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g"
#define EEPROM_LABEL_ERROR_LED_BRINK_PERIOD                     "�G���[LED�̓_�Ŏ���"
#define EEPROM_LABEL_COM_TIMEOUT_LIMIT                          "�ʐM�^�C���A�E�g���o����"
 /*! @} */


/**
 * @name    EEPROM�f�[�^�T�C�Y
 */
/*! @{ */
#define EEPROM_SIZE_MAX                                         4       /*!< �ő�T�C�Y */
#define EEPROM_SIZE_SERVO_INITIAL_CTRL_MODE                     1       /*!< �T�[�{���䃂�[�h�C�������[�h */
#define EEPROM_SIZE_SERVO_POSITION_FACTOR                       1       /*!< �T�[�{�p�x�ʒu�ϊ��W�� */
#define EEPROM_SIZE_PAN_SERVO_INITIAL_ANGLE                     2       /*!< ���������p�T�[�{�C�����p�x */
#define EEPROM_SIZE_PAN_SERVO_NEUTRAL_POSITION                  2       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define EEPROM_SIZE_PAN_SERVO_MIN_POSITION                      2       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define EEPROM_SIZE_PAN_SERVO_MAX_POSITION                      2       /*!< ���������p�T�[�{�C�ő�ʒu */
#define EEPROM_SIZE_TILT_SERVO_INITIAL_ANGLE                    2       /*!< ���������p�T�[�{�C�����p�x */
#define EEPROM_SIZE_TILT_SERVO_NEUTRAL_POSITION                 2       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define EEPROM_SIZE_TILT_SERVO_MIN_POSITION                     2       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define EEPROM_SIZE_TILT_SERVO_MAX_POSITION                     2       /*!< ���������p�T�[�{�C�ő�ʒu */
#define EEPROM_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT         1       /*!< �X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g */
#define EEPROM_SIZE_ERROR_LED_BRINK_PERIOD                      1       /*!< �G���[LED�̓_�Ŏ��� */
#define EEPROM_SIZE_COM_TIMEOUT_LIMIT                           1       /*!< �ʐM�^�C���A�E�g���o���� */
/*! @} */


/**
 * @name    EEPROM�C���f�b�N�X
 */
/*! @{ */
#define EEPROM_SERVO_INITIAL_CTRL_MODE                          0       /*!< �T�[�{���䃂�[�h�C�������[�h */
#define EEPROM_SERVO_POSITION_FACTOR                            1       /*!< �T�[�{�p�x�ʒu�ϊ��W�� */
#define EEPROM_PAN_SERVO_INITIAL_ANGLE                          2       /*!< ���������p�T�[�{�C�����p�x */
#define EEPROM_PAN_SERVO_NEUTRAL_POSITION                       3       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define EEPROM_PAN_SERVO_MIN_POSITION                           4       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define EEPROM_PAN_SERVO_MAX_POSITION                           5       /*!< ���������p�T�[�{�C�ő�ʒu */
#define EEPROM_TILT_SERVO_INITIAL_ANGLE                         6       /*!< ���������p�T�[�{�C�����p�x */
#define EEPROM_TILT_SERVO_NEUTRAL_POSITION                      7       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define EEPROM_TILT_SERVO_MIN_POSITION                          8       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define EEPROM_TILT_SERVO_MAX_POSITION                          9       /*!< ���������p�T�[�{�C�ő�ʒu */
#define EEPROM_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT              10      /*!< �X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g */
#define EEPROM_ERROR_LED_BRINK_PERIOD                           11      /*!< �G���[LED�̓_�Ŏ��� */
#define EEPROM_COM_TIMEOUT_LIMIT                                12      /*!< �ʐM�^�C���A�E�g���o���� */
#define EEPROM_INDEX_NUM                                        13      /*!< EEPROM�C���f�b�N�X�̐� */
/*! @} */


/**
 * @struct  eeprom_st
 * @brief   EEPROM���\����
 *
 * @typedef EEPROM_T
 * @brief   EEPROM���\����
 */
typedef struct eeprom_st {
    LPCTSTR label;              /*!< EEPROM���x�� */
    DWORD size;                 /*!< EEPROM�f�[�^�T�C�Y */
    BOOL sign;                  /*!< EEPROM�f�[�^���� */
    BOOL write_enable;          /*!< EEPROM���C�g�C�l�[�u�� */
} EEPROM_T;


/**
 * @brief   EEPROM�̑��݊m�F
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @retval          TRUE            EEPROM�͑��݂���
 * @retval          FALSE           EEPROM�͑��݂��Ȃ�
 */
BOOL CameraMount_eepromExists(DWORD eepromIndex);


/**
 * @brief   EEPROM�f�[�^�T�C�Y�擾����
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @return          EEPROM�f�[�^�T�C�Y
 */
DWORD CameraMount_getEEPROMSize(DWORD eepromIndex);


/**
 * @brief   EEPROM�Ǎ��ݏ���
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @return          EEPROM�Ǎ��݃f�[�^�i�[��̃|�C���^
 */
LPVOID CameraMount_readEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);


/**
 * @brief   EEPROM�����ݏ���
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 * @param[in]       data            EEPROM�����݃f�[�^�i�[��̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CameraMount_writeEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex, LPVOID data);


/**
 * @brief   EEPROM�f�[�^�\������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 */
VOID CameraMount_printEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);


/**
 * @brief   �SEEPROM�f�[�^�\������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 */
VOID CameraMount_printAllEEPROM(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   ���W�X�^�f�[�^�ҏW����
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       eepromIndex     EEPROM�C���f�b�N�X
 */
BOOL CameraMount_editEEPROM(CAMERAMOUNT_T *cameraMount, DWORD eepromIndex);

#endif  /* __CAMERAMOUNT_EEPROM_H__ */
