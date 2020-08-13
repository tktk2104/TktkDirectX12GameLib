#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	ComponentBase::ComponentBase(float drawPriority, const int collisionGroup)
		: m_drawPriority(drawPriority)
		, m_collisionGroup(collisionGroup)
	{
	}

	ComponentBase::~ComponentBase()
	{
	}

	float ComponentBase::getDrawPriority() const
	{
		return m_drawPriority;
	}

	int ComponentBase::getCollisionGroup() const
	{
		return m_collisionGroup;
	}

	void ComponentBase::setActive(bool activeFlag)
	{
		m_nextFrameActive = activeFlag;
	}

	void ComponentBase::destroy()
	{
		m_isDead = true;
	}

	bool ComponentBase::isActive() const
	{
		if (m_user.expired()) return m_isActive;

		if (!m_user->isActive()) return false;

		return m_isActive;
	}

	bool ComponentBase::isDead() const
	{
		return m_isDead;
	}

	bool ComponentBase::activeChangeCheck()
	{
		if (m_isActive != m_nextFrameActive)
		{
			m_isActive = m_nextFrameActive;
			return true;
		}
		return false;
	}

	const GameObjectPtr& ComponentBase::getGameObject() const
	{
		return m_user;
	}

	void ComponentBase::setUser(const GameObjectPtr& user)
	{
		m_user = user;
	}
}