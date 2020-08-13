#include "TktkDX12Game/Component/ComponentStartFunc/ComponentStartRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentStartRunner::runStart()
	{
		if (m_afterRun) return;

		if (m_componentPtr.expired()) return;

		if (m_componentPtr.lock()->isActive())
		{
			m_vtablePtr->runStart(m_componentPtr);
			m_afterRun = true;
		}
	}

	bool ComponentStartRunner::isDead() const
	{
		return (m_afterRun || m_componentPtr.expired() || m_componentPtr.lock()->isDead());
	}
}