#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardClippingDrawerMaker.h"

namespace tktk
{
	BillboardClippingDrawerMaker BillboardClippingDrawerMaker::m_self;

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BillboardClippingDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BillboardClippingDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// �g�p����J�����n���h���̃f�t�H���g�l�̓f�t�H���g�ʏ�J����
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BillboardClippingDrawer> BillboardClippingDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<BillboardClippingDrawer>(
				m_drawPriority,
				m_billboardMaterialHandle,
				m_useRtvDescriptorHeapHandle,
				m_cameraHandle,
				m_centerRate,
				m_blendRate,
				m_clippingParam
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<BillboardClippingDrawer>(
			m_drawPriority,
			m_billboardMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_cameraHandle,
			m_centerRate,
			m_blendRate,
			m_clippingParam
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::billboardMaterialHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_billboardMaterialHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::cameraHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::cameraId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::billboardMaterialId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(value);
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_centerRate = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::blendRate(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_blendRate = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingParam.leftTopPos = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingParam.size = value;
		return *this;
	}
}