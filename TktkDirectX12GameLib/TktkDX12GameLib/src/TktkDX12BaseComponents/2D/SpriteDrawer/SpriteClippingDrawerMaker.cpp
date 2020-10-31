#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteClippingDrawerMaker.h"

namespace tktk
{
	SpriteClippingDrawerMaker SpriteClippingDrawerMaker::m_self;

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SpriteClippingDrawerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SpriteClippingDrawer> SpriteClippingDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<SpriteClippingDrawer>(
				m_drawPriority,
				m_spriteMaterialHandle,
				m_useRtvDescriptorHeapHandle,
				m_centerRate,
				m_clippingParam
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<SpriteClippingDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_centerRate,
			m_clippingParam
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_spriteMaterialHandle = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_centerRate = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingParam.leftTopPos = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_clippingParam.size = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}
}