#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* class member */
#include "TktkDX12Game/EventMessage/MessageTypeCarrier.h"

namespace tktk
{
	/* funcUseType */
	class MessageAttachment;

	// ����̃��b�Z�[�W���擾�����玩�g��GameObject���폜����
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		explicit ReceiveMessageToSelfDestroyer(MessageTypeCarrier destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(MessageTypeCarrier messageId, const tktk::MessageAttachment& value);

	private:

		// ���g���폜���郁�b�Z�[�W�̎��
		MessageTypeCarrier m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_