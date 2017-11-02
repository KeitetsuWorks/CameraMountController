/**
 * @file        CameraMount_Register.h
 * @brief       �J�����}�E���g�R���g���[�� ���W�X�^�C���^�t�F�[�X
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_REGISTER_H__
#define __CAMERAMOUNT_REGISTER_H__


/**
 * @name    ���W�X�^���x��
 */
 /*! @{ */
#define REGISTER_LABEL_SYSTEM_STATE                             "�V�X�e���X�e�[�g"
#define REGISTER_LABEL_SYSTEM_STATUS                            "�V�X�e���X�e�[�^�X"
#define REGISTER_LABEL_SYSTEM_ERROR                             "�V�X�e���G���["
#define REGISTER_LABEL_SERVO_CTRL_MODE                          "�T�[�{���䃂�[�h"
#define REGISTER_LABEL_SERVO_POSITION_FACTOR                    "�T�[�{�p�x�ʒu�ϊ��W��"
#define REGISTER_LABEL_PAN_SERVO_REQUEST_ANGLE                  "���������p�T�[�{�C�w���p�x"
#define REGISTER_LABEL_PAN_SERVO_REQUEST_POSITION               "���������p�T�[�{�C�w���ʒu"
#define REGISTER_LABEL_PAN_SERVO_NEUTRAL_POSITION               "���������p�T�[�{�C�j���[�g�����ʒu"
#define REGISTER_LABEL_PAN_SERVO_MIN_POSITION                   "���������p�T�[�{�C�ŏ��ʒu"
#define REGISTER_LABEL_PAN_SERVO_MAX_POSITION                   "���������p�T�[�{�C�ő�ʒu"
#define REGISTER_LABEL_TILT_SERVO_REQUEST_ANGLE                 "���������p�T�[�{�C�w���p�x"
#define REGISTER_LABEL_TILT_SERVO_REQUEST_POSITION              "���������p�T�[�{�C�w���ʒu"
#define REGISTER_LABEL_TILT_SERVO_NEUTRAL_POSITION              "���������p�T�[�{�C�j���[�g�����ʒu"
#define REGISTER_LABEL_TILT_SERVO_MIN_POSITION                  "���������p�T�[�{�C�ŏ��ʒu"
#define REGISTER_LABEL_TILT_SERVO_MAX_POSITION                  "���������p�T�[�{�C�ő�ʒu"
#define REGISTER_LABEL_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT      "�X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g"
#define REGISTER_LABEL_ERROR_LED_BRINK_PERIOD                   "�G���[LED�̓_�Ŏ���"
#define REGISTER_LABEL_COM_TIMEOUT_LIMIT                        "�ʐM�^�C���A�E�g���o����"
 /*! @} */


/**
 * @name    ���W�X�^�f�[�^�T�C�Y
 */
/*! @{ */
#define REGISTER_SIZE_SYSTEM_STATE                              1       /*!< �V�X�e���X�e�[�g */
#define REGISTER_SIZE_SYSTEM_STATUS                             1       /*!< �V�X�e���X�e�[�^�X */
#define REGISTER_SIZE_SYSTEM_ERROR                              1       /*!< �V�X�e���G���[ */
#define REGISTER_SIZE_SERVO_CTRL_MODE                           1       /*!< �T�[�{���䃂�[�h */
#define REGISTER_SIZE_SERVO_POSITION_FACTOR                     1       /*!< �T�[�{�p�x�ʒu�ϊ��W�� */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_ANGLE                   2       /*!< ���������p�T�[�{�C�w���p�x */
#define REGISTER_SIZE_PAN_SERVO_REQUEST_POSITION                2       /*!< ���������p�T�[�{�C�w���ʒu */
#define REGISTER_SIZE_PAN_SERVO_NEUTRAL_POSITION                2       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define REGISTER_SIZE_PAN_SERVO_MIN_POSITION                    2       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define REGISTER_SIZE_PAN_SERVO_MAX_POSITION                    2       /*!< ���������p�T�[�{�C�ő�ʒu */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_ANGLE                  2       /*!< ���������p�T�[�{�C�w���p�x */
#define REGISTER_SIZE_TILT_SERVO_REQUEST_POSITION               2       /*!< ���������p�T�[�{�C�w���ʒu */
#define REGISTER_SIZE_TILT_SERVO_NEUTRAL_POSITION               2       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define REGISTER_SIZE_TILT_SERVO_MIN_POSITION                   2       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define REGISTER_SIZE_TILT_SERVO_MAX_POSITION                   2       /*!< ���������p�T�[�{�C�ő�ʒu */
#define REGISTER_SIZE_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT       1       /*!< �X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g */
#define REGISTER_SIZE_ERROR_LED_BRINK_PERIOD                    1       /*!< �G���[LED�̓_�Ŏ��� */
#define REGISTER_SIZE_COM_TIMEOUT_LIMIT                         1       /*!< �ʐM�^�C���A�E�g���o���� */
/*! @} */


/**
 * @name    ���W�X�^�C���f�b�N�X
 */
/*! @{ */
#define REGISTER_SYSTEM_STATE                                   0       /*!< �V�X�e���X�e�[�g */
#define REGISTER_SYSTEM_STATUS                                  1       /*!< �V�X�e���X�e�[�^�X */
#define REGISTER_SYSTEM_ERROR                                   2       /*!< �V�X�e���G���[ */
#define REGISTER_SERVO_CTRL_MODE                                3       /*!< �T�[�{���䃂�[�h */
#define REGISTER_SERVO_POSITION_FACTOR                          4       /*!< �T�[�{�p�x�ʒu�ϊ��W�� */
#define REGISTER_PAN_SERVO_REQUEST_ANGLE                        5       /*!< ���������p�T�[�{�C�w���p�x */
#define REGISTER_PAN_SERVO_REQUEST_POSITION                     6       /*!< ���������p�T�[�{�C�w���ʒu */
#define REGISTER_PAN_SERVO_NEUTRAL_POSITION                     7       /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define REGISTER_PAN_SERVO_MIN_POSITION                         8       /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define REGISTER_PAN_SERVO_MAX_POSITION                         9       /*!< ���������p�T�[�{�C�ő�ʒu */
#define REGISTER_TILT_SERVO_REQUEST_ANGLE                       10      /*!< ���������p�T�[�{�C�w���p�x */
#define REGISTER_TILT_SERVO_REQUEST_POSITION                    11      /*!< ���������p�T�[�{�C�w���ʒu */
#define REGISTER_TILT_SERVO_NEUTRAL_POSITION                    12      /*!< ���������p�T�[�{�C�j���[�g�����ʒu */
#define REGISTER_TILT_SERVO_MIN_POSITION                        13      /*!< ���������p�T�[�{�C�ŏ��ʒu */
#define REGISTER_TILT_SERVO_MAX_POSITION                        14      /*!< ���������p�T�[�{�C�ő�ʒu */
#define REGISTER_STATUS_LED_BRINK_PERIOD_COM_TIMEOUT            15      /*!< �X�e�[�^�XLED�̓_�Ŏ����C�ʐM�^�C���A�E�g */
#define REGISTER_ERROR_LED_BRINK_PERIOD                         16      /*!< �G���[LED�̓_�Ŏ��� */
#define REGISTER_COM_TIMEOUT_LIMIT                              17      /*!< �ʐM�^�C���A�E�g���o���� */
#define REGISTER_INDEX_NUM                                      18      /*!< ���W�X�^�C���f�b�N�X�̐� */
/*! @} */


/**
 * @struct  register_st
 * @brief   ���W�X�^���\����
 *
 * @typedef REGISTER_T
 * @brief   ���W�X�^���\����
 */
typedef struct register_st {
    LPCTSTR label;              /*!< ���W�X�^���x�� */
    DWORD size;                 /*!< ���W�X�^�f�[�^�T�C�Y */
    BOOL sign;                  /*!< ���W�X�^�f�[�^���� */
    BOOL write_enable;          /*!< ���W�X�^���C�g�C�l�[�u�� */
} REGISTER_T;


/**
 * @brief   ���W�X�^�̑��݊m�F
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @retval          TRUE            ���W�X�^�͑��݂���
 * @retval          FALSE           ���W�X�^�͑��݂��Ȃ�
 */
BOOL CameraMount_registerExists(DWORD registerIndex);


/**
 * @brief   ���W�X�^�f�[�^�T�C�Y�擾����
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @return          ���W�X�^�f�[�^�T�C�Y
 */
DWORD CameraMount_getRegisterSize(DWORD registerIndex);


/**
 * @brief   ���W�X�^�Ǎ��ݏ���
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @return          ���W�X�^�Ǎ��݃f�[�^�i�[��̃|�C���^
 */
LPVOID CameraMount_readRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   ���W�X�^�����ݏ���
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 * @param[in]       data            ���W�X�^�����݃f�[�^�i�[��̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CameraMount_writeRegister(CAMERAMOUNT_T *cameraMount, DWORD registerIndex, LPVOID data);


/**
 * @brief   ���W�X�^�f�[�^�\�������i���W�X�^�C���f�b�N�X�w��j
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 */
VOID CameraMount_printRegister_i(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   ���W�X�^�f�[�^�\������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 */
VOID CameraMount_printRegister(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   �S���W�X�^�f�[�^�\������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 */
VOID CameraMount_printAllRegister(CAMERAMOUNT_T *cameraMount);


/**
 * @brief   ���W�X�^�f�[�^�ҏW�����i���W�X�^�C���f�b�N�X�w��j
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 * @param[in]       registerIndex   ���W�X�^�C���f�b�N�X
 */
BOOL CameraMount_editRegister_i(CAMERAMOUNT_T *cameraMount, DWORD registerIndex);


/**
 * @brief   ���W�X�^�f�[�^�ҏW����
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\����
 */
BOOL CameraMount_editRegister(CAMERAMOUNT_T *cameraMount);

#endif  /* __CAMERAMOUNT_REGISTER_H__ */
