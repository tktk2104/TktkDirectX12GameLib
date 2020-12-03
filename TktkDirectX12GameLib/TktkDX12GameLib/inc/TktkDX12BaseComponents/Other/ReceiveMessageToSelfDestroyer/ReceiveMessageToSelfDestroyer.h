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

	// 特定のメッセージを取得したら自身のGameObjectを削除する
	class ReceiveMessageToSelfDestroyer
		: public ComponentBase
	{
	public:

		explicit ReceiveMessageToSelfDestroyer(MessageTypeCarrier destroyMessegeType);

	public:

		// <PolymorphismFunc>
		void handleMessage(MessageTypeCarrier messageId, const tktk::MessageAttachment& value);

	private:

		// 自身を削除するメッセージの種類
		MessageTypeCarrier m_destroyMessegeType;
	};
}
#endif // !RECEIVE_MESSAGE_TO_SELF_DESTROYER_H_