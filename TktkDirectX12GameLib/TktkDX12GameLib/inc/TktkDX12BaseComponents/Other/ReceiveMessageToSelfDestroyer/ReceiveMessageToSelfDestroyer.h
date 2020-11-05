#ifndef RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_
#define RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// ����̃��b�Z�[�W���擾�����玩�g��GameObject���폜����
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		ReceiveMessageToSelfDestroyer(MessageTypeCarrier destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(MessageTypeCarrier messageId, const tktk::MessageAttachment& value);

	private:

		// ���g���폜���郁�b�Z�[�W�̎��
		MessageTypeCarrier m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_