/**
 * @file        CameraMount.h
 * @brief       �J�����}�E���g�R���g���[��
 * @author      Keitetsu
 * @date        2016/12/18
 * @copyright   Copyright (c) 2016 Keitetsu
 * @par         License
 *              This software is released under the MIT License.
 */

#ifndef __CAMERAMOUNT_H__
#define __CAMERAMOUNT_H__

#include "CommandIF.h"


/**
 * @name    �J�����}�E���g�R���g���[���Ή��o�[�W����
 */
/*! @{ */
#define CAMERAMOUNT_SUPPORTED_TYPE          0x43        /*!< �f�o�C�X�^�C�v */
#define CAMERAMOUNT_SUPPORTED_VERSION       3           /*!< �f�o�C�X�o�[�W���� */
#define CAMERAMOUNT_SUPPORTED_REVISION      0           /*!< �f�o�C�X���r�W���� */
/*! @} */


/**
 * @struct  CameraMount_st
 * @brief   �J�����}�E���g�R���g���[�����\����
 *
 * @typedef CAMERAMOUNT_T
 * @brief   �J�����}�E���g�R���g���[�����\����
 *
 * @typedef CAMERAMOUNT
 * @brief   �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 */
typedef struct CameraMount_st {
    COMMANDIF cmdIF;                /*!< �R�}���h�C���^�t�F�[�X���\���̂̃|�C���^ */
} CAMERAMOUNT_T, *CAMERAMOUNT;


/**
 * @brief   �J�����}�E���g�R���g���[�����J��
 * @param[in]       comName         �V���A���|�[�g��
 * @retval          NULL            �ُ�I��
 * @retval          Others          �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 */
CAMERAMOUNT CameraMount_open(LPCTSTR comName);


/**
 * @brief   �J�����}�E���g�R���g���[�������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 * @retval          NULL            ����I��
 * @retval          Others          �ُ�I��
 */
CAMERAMOUNT CameraMount_close(CAMERAMOUNT cameraMount);


/**
 * @brief   �J�����}�E���g�R���g���[�������Z�b�g����
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CameraMount_reset(CAMERAMOUNT cameraMount);


/**
 * @brief   �J�����}�E���g�R���g���[��������������
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 * @retval          TRUE            ����I��
 * @retval          FALSE           �ُ�I��
 */
BOOL CameraMount_initialize(CAMERAMOUNT cameraMount);


/**
 * @brief   �J�����}�E���g�R���g���[���̃o�[�W�������\������
 * @param[in,out]   cameraMount     �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 */
VOID CameraMount_printVersion(CAMERAMOUNT cameraMount);


/**
 * @brief   �J�����}�E���g�R���g���[�����Ή��o�[�W���������؂���
 * @param[in]       cameraMount     �J�����}�E���g�R���g���[�����\���̂̃|�C���^
 * @retval          TRUE            �Ή��o�[�W����
 * @retval          FALSE           ��Ή��o�[�W����
 */
BOOL CameraMount_validateVersion(CAMERAMOUNT cameraMount);

#endif  /* __CAMERAMOUNT_H__ */
