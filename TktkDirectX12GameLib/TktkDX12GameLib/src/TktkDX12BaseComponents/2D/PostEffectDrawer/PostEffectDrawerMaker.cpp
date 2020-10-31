#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = PostEffectDrawerMaker();
		
		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h���̃f�t�H���g�l�̓o�b�N�o�b�t�@
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<PostEffectDrawer>(
				m_drawPriority,
				m_postEffectMaterialHandle,
				m_useRtvDescriptorHeapHandle
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectMaterialHandle,
			m_useRtvDescriptorHeapHandle
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::useRtvDescriptorHeapId(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialHandle(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_postEffectMaterialHandle = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialIdImpl(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_postEffectMaterialHandle = DX12GameManager::getPostEffectMaterialHandle(value);
		return *this;
	}
}