#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker& SpriteDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SpriteDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::makeStart(const StateTypeHierarchy&& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SpriteDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<SpriteDrawer>(
				m_drawPriority,
				m_spriteMaterialHandle,
				m_useRtvDescriptorHeapHandle,
				m_centerRate
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_centerRate
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_spriteMaterialHandle = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_centerRate = value;
		return *this;
	}
}