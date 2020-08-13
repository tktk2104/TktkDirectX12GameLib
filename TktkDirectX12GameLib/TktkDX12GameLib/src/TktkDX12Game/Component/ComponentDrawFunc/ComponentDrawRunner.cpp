#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentDrawRunner::runDraw()
	{
		if (m_componentPtr.expired()) return;

		if (m_componentPtr.lock()->isActive())
		{
			m_vtablePtr->runDraw(m_componentPtr);
		}
	}

	bool ComponentDrawRunner::isDead() const
	{
		return (m_componentPtr.expired() || m_componentPtr.lock()->isDead());
	}
}