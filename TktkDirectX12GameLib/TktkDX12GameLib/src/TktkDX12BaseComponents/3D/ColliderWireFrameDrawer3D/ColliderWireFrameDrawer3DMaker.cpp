#include"TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ColliderWireFrameDrawer3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
		return m_user->createComponent<ColliderWireFrameDrawer3D>(
			m_drawPriority,
			m_cameraHandle,
			m_shadowMapCameraHandle,
			m_lightHandle,
			m_useRtvDescriptorHeapHandle,
			m_lineColor
			);
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_shadowMapCameraHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lightHandle = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lineColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineColor = value;
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::cameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::shadowMapCameraIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lightIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lightHandle = DX12GameManager::getLightHandle(value);
		return *this;
	}
}