#include "TktkDX12Game/Component/ComponentGameObjectFunc/ComponentGameObjectFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	const ComponentBasePtr& ComponentGameObjectFuncRunner::getComponentBasePtr() const
	{
		return m_selfPtr;
	}

	void ComponentGameObjectFuncRunner::runHandleMessage(const MessageAttachment& value, unsigned int messageId)
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runHandleMessage(m_selfPtr, messageId, value);
	}

	void ComponentGameObjectFuncRunner::runAfterChangeParent(const GameObjectPtr& beforParent)
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runAfterChangeParent(m_selfPtr, beforParent);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionEnter(const GameObjectPtr& other)
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionEnter(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionStay(const GameObjectPtr& other)
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionStay(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionExit(const GameObjectPtr& other)
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionExit(m_selfPtr, other);
	}

	bool ComponentGameObjectFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	void ComponentGameObjectFuncRunner::destroy()
	{
		if (m_selfPtr.isDead()) return;
		m_selfPtr->destroy();
	}
}