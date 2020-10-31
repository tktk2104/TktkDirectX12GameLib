#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyerMaker ReceiveMessageToSelfDestroyerMaker::m_self;

	ReceiveMessageToSelfDestroyerMaker & ReceiveMessageToSelfDestroyerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ReceiveMessageToSelfDestroyerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ReceiveMessageToSelfDestroyer> ReceiveMessageToSelfDestroyerMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.empty())
		{
			return m_user->createComponent<ReceiveMessageToSelfDestroyer>(m_destroyMessegeType);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<ReceiveMessageToSelfDestroyer>(m_destroyMessegeType);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	ReceiveMessageToSelfDestroyerMaker& ReceiveMessageToSelfDestroyerMaker::destroyMessegeTypeImpl(unsigned int value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}