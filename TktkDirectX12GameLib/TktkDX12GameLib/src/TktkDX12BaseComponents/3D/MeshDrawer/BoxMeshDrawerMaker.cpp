#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshDrawerMaker.h"

namespace tktk
{
    BoxMeshDrawerMaker BoxMeshDrawerMaker::m_self;

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::makeStart(GameObjectPtr user)
    {
        // �ϐ�������������
        m_self = BoxMeshDrawerMaker();

        // �����̃��[�U�[��ݒ�
        m_self.m_user = user;

        // �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
        m_self.m_useResourceHandles.cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

        // �g�p����V���h�E�}�b�v�J�����n���h���̃f�t�H���g�l�̓f�t�H���g�V���h�E�}�b�v�J����
        m_self.m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

        // �g�p���郉�C�g�n���h���̃f�t�H���g�l�̓f�t�H���g���C�g
        m_self.m_useResourceHandles.lightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

        // �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
        m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

        // ���g�̎Q�Ƃ�Ԃ�
        return m_self;
    }

    ComponentPtr<BoxMeshDrawer> BoxMeshDrawerMaker::create()
    {
        // �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
        return m_user->createComponent<BoxMeshDrawer>(
            m_drawPriority,
            m_boxSize,
            m_localPosition,
            m_albedoColor,
            m_useResourceHandles
            );
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::drawPriority(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_drawPriority = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::boxSize(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_boxSize = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::localPosition(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_localPosition = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_albedoColor = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.rtvDescriptorHeapHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraHandle(unsigned int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.cameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.shadowMapCameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightHandle(unsigned int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.lightHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraIdImpl(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraIdImpl(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightIdImpl(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
        return *this;
    }
}