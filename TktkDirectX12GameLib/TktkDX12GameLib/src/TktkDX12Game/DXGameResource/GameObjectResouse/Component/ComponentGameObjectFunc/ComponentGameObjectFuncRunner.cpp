#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentGameObjectFunc/ComponentGameObjectFuncRunner.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	ComponentGameObjectFuncRunner::ComponentGameObjectFuncRunner(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr)
		: m_selfPtr(componentPtr)
		, m_vtablePtr(vtablePtr)
	{
	}

	const ComponentBasePtr& ComponentGameObjectFuncRunner::getComponentBasePtr() const
	{
		return m_selfPtr;
	}

	void ComponentGameObjectFuncRunner::runHandleMessage(MessageTypeCarrier type, const MessageAttachment& attachment) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->handleMessage(m_selfPtr, type, attachment);
	}

	void ComponentGameObjectFuncRunner::runAfterChangeParent(const GameObjectPtr& beforParent) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->afterChangeParent(m_selfPtr, beforParent);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionEnter(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->onCollisionEnter(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionStay(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->onCollisionStay(m_selfPtr, other);
	}

	void ComponentGameObjectFuncRunner::runOnCollisionExit(const GameObjectPtr& other) const
	{
		if (m_selfPtr.isDead()) return;
		m_vtablePtr->onCollisionExit(m_selfPtr, other);
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