#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<ReceiveMessageToSelfDestroyer>(m_destroyMessegeType);
	}

	ReceiveMessageToSelfDestroyerMaker& ReceiveMessageToSelfDestroyerMaker::destroyMessegeType(MessageTypeCarrier value)
	{
		m_destroyMessegeType = value;
		return *this;
	}
}