#include "TktkDX12Game/Component/ComponentGameObjectFunc/ComponentGameObjectFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	const ComponentBasePtr& ComponentGameObjectFuncRunner::getComponentBasePtr() const
	{
		return m_selfPtr;
	}

	void ComponentGameObjectFuncRunner::runHandleMessage(MessageTypeCarrier type, const MessageAttachment& attachment) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runHandleMessage(m_selfPtr, type, attachment);
	}

	void ComponentGameObjectFuncRunner::runAfterChangeParent(const GameObjectPtr& beforParent) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runAfterChangeParent(m_selfPtr, beforParent);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionEnter(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionEnter(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionStay(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionStay(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionExit(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->runOnCollisionExit(m_selfPtr, other);
	}

	bool ComponentGameObjectFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	void ComponentGameObjectFuncRunner::destroy() const
	{
		if (m_selfPtr.isDead()) return;
		m_selfPtr->destroy();
	}
}