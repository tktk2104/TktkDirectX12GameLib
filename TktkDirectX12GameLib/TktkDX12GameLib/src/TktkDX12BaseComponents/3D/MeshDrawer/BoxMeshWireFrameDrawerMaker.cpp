#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshWireFrameDrawerMaker.h"

namespace tktk
{
	BoxMeshWireFrameDrawerMaker BoxMeshWireFrameDrawerMaker::m_self;

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BoxMeshWireFrameDrawerMaker();

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

	ComponentPtr<BoxMeshWireFrameDrawer> BoxMeshWireFrameDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<BoxMeshWireFrameDrawer>(
				m_drawPriority,
				m_boxSize,
				m_localPosition,
				m_albedoColor,
				m_useResourceHandles
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<BoxMeshWireFrameDrawer>(
			m_drawPriority,
			m_boxSize,
			m_localPosition,
			m_albedoColor,
			m_useResourceHandles
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::boxSize(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_boxSize = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::localPosition(const tktkMath::Vector3& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_localPosition = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::albedoColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_albedoColor = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.rtvDescriptorHeapHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::cameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::shadowMapCameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::lightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = value;
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::cameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::shadowMapCameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BoxMeshWireFrameDrawerMaker& BoxMeshWireFrameDrawerMaker::lightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}