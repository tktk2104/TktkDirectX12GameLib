#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachine.h"

#include <stdexcept>
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/CurStateTypeList.h"

namespace tktk
{
	StateMachine::StateMachine(StateTypeCarrier stateType)
		: m_selfStateType(stateType)
	{
	}

	void StateMachine::onDisable()
	{
		for (auto& node : m_gameObjectList)
		{
			node->setActive(false);
		}

		for (auto& node : m_componentList)
		{
			node->setActive(false);
		}
	}

	void StateMachine::start()
	{
		m_curStateTypeList = getComponent<CurStateTypeList>();

		if (m_curStateTypeList.expired())
		{
			throw std::runtime_error("StateMachine not found CurStateTypeList");
		}
	}

	void StateMachine::update()
	{
		bool activeFlag = m_curStateTypeList->contain(m_selfStateType);

		for (auto& node : m_gameObjectList)
		{
			node->setActive(activeFlag);
		}

		for (auto& node : m_componentList)
		{
			node.setActive(activeFlag);
		}
	}

	void StateMachine::addChild(const GameObjectPtr& child)
	{
		child->setActive(false);

		m_gameObjectList.push_front(child);
	}

	void StateMachine::addComponent(const ComponentBasePtr& componentPtr)
	{
		componentPtr.setActive(false);

		m_componentList.push_front(componentPtr);
	}
}
