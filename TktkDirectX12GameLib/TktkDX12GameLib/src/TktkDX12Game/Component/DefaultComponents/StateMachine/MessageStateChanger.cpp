#include "TktkDX12Game/Component/DefaultComponents/StateMachine/MessageStateChanger.h"

namespace tktk
{
	MessageStateChanger::MessageStateChanger(unsigned int messageType, const std::vector<int>& enableStateArray, const std::vector<int>& disableStateArray)
		: m_messageType(messageType)
		, m_enableStateArray(enableStateArray)
		, m_disableStateArray(disableStateArray)
	{
	}

	void MessageStateChanger::handleMessage(unsigned int messageId, const tktk::MessageAttachment& value)
	{
		if (messageId == m_messageType)
		{
			for (int enableState : m_enableStateArray)
			{
				getGameObject()->stateEnable(enableState);
			}

			for (int disableState : m_disableStateArray)
			{
				getGameObject()->stateDisable(disableState);
			}
		}
	}
}