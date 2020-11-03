#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateChangeTimer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	StateChangeTimer::StateChangeTimer(float stateChangeTimeSec, const StateTypeList& enableStateArray, const StateTypeList& disableStateArray)
		: m_stateChangeTimeSec(stateChangeTimeSec)
		, m_enableStateArray(enableStateArray)
		, m_disableStateArray(disableStateArray)
	{
	}

	void StateChangeTimer::onEnable()
	{
		m_stateChangeTimer = 0.0f;
		m_afterChange = false;
	}

	void StateChangeTimer::update()
	{
		if (m_afterChange) return;

		m_stateChangeTimer += DX12GameManager::deltaTime();

		if (m_stateChangeTimer > m_stateChangeTimeSec)
		{
			for (const auto& enableState : m_enableStateArray.list)
			{
				getGameObject()->stateEnable(enableState);
			}

			for (const auto& disableState : m_disableStateArray.list)
			{
				getGameObject()->stateDisable(disableState);
			}
			m_afterChange = true;
		}
	}
}