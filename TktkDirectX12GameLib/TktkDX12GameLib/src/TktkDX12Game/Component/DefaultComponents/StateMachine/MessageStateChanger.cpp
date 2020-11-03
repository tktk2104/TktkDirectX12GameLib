#include "TktkDX12Game/Component/DefaultComponents/StateMachine/MessageStateChanger.h"

namespace tktk
{
	MessageStateChanger::MessageStateChanger(MessageTypeCarrier type, const StateTypeList& enableStateArray, const StateTypeList& disableStateArray)
		: m_messageType(type)
		, m_enableStateArray(enableStateArray)
		, m_disableStateArray(disableStateArray)
	{
	}

	void MessageStateChanger::handleMessage(MessageTypeCarrier type, const tktk::MessageAttachment& value)
	{
		if (!isActive()) return;

		if (type == m_messageType)
		{
			for (const auto& enableState : m_enableStateArray.list)
			{
				getGameObject()->stateEnable(enableState);
			}

			for (const auto& disableState : m_disableStateArray.list)
			{
				getGameObject()->stateDisable(disableState);
			}
		}
	}
}