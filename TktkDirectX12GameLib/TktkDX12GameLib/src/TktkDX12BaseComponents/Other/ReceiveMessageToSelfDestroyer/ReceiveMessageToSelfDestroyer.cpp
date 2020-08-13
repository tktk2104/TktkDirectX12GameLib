#include "TktkDX12BaseComponents/Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyer.h"

namespace tktk
{
	ReceiveMessageToSelfDestroyer::ReceiveMessageToSelfDestroyer(
		int destroyMessegeType
	)
		: m_destroyMessegeType(destroyMessegeType)
	{
	}

	void ReceiveMessageToSelfDestroyer::handleMessage(unsigned int messageId, const tktk::MessageAttachment& value)
	{
		if (messageId == m_destroyMessegeType)
		{
			getGameObject()->destroy();
		}
	}
}