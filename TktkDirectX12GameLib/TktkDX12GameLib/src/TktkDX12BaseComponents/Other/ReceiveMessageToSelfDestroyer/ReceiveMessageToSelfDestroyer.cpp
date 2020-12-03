#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyer.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyer::ReceiveMessageToSelfDestroyer(MessageTypeCarrier destroyMessegeType)
		: m_destroyMessegeType(destroyMessegeType)
	{
	}

	void ReceiveMessageToSelfDestroyer::handleMessage(MessageTypeCarrier messageId, const tktk::MessageAttachment& value)
	{
		if (messageId == m_destroyMessegeType)
		{
			getGameObject()->destroy();
		}
	}
}