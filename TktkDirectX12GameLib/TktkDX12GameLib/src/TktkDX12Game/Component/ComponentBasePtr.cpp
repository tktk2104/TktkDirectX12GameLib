#include "TktkDX12Game/Component/ComponentBasePtr.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	std::shared_ptr<ComponentBase> ComponentBasePtr::operator->() const
	{
		if (m_componentPtr.expired()) return nullptr;
		return m_componentPtr.lock();
	}

	bool ComponentBasePtr::isSame(const ComponentBasePtr& other) const
	{
		if (m_componentPtr.expired() && other.m_componentPtr.expired()) return true;
		if (m_componentPtr.expired() || other.m_componentPtr.expired()) return false;
		return (m_componentPtr.lock() == other.m_componentPtr.lock());
	}

	void ComponentBasePtr::setActive(bool isActive) const
	{
		if (m_componentPtr.expired()) return;
		m_componentPtr.lock()->setActive(isActive);
	}

	bool ComponentBasePtr::isDead() const
	{
		return (m_componentPtr.expired() || m_componentPtr.lock()->isDead());
	}
}