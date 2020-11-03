#include "TktkDX12Game/GameObject/GameObject.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/GameObject/GameObjectTagList.h"
#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ParentChildManager.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachine.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineList.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/CurStateTypeList.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateChangeTimer.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/MessageStateChanger.h"

namespace tktk
{
	GameObject::GameObject()
	{
		m_tagList				= std::make_unique<GameObjectTagList>();
		m_componentList			= std::make_unique<GameObjectComponentList>();
		m_parentChildManager	= createComponent<ParentChildManager>();
	}

	GameObject::~GameObject()
	{
		m_componentList->destroyAll();
	}

	void GameObject::update()
	{
		m_parentChildManager->updateContainer();

		m_componentList->movePreFrameAddedNode();
		m_componentList->removeDeadComponent();
		m_componentList->clearHitObjectList();

		m_isActive = m_nextFrameActive;
	}

	void GameObject::setActive(bool activeFlag)
	{
		m_nextFrameActive = activeFlag;
	}

	void GameObject::destroy()
	{
		m_isDead = true;

		m_parentChildManager->destroyChildren();

		m_componentList->destroyAll();
	}

	bool GameObject::isActive() const
	{
		if (!m_isActive) return false;

		if (getParent().expired()) return true;

		return getParent()->isActive();
	}

	bool GameObject::isDead() const
	{
		return m_isDead;
	}

	void GameObject::addGameObjectTag(GameObjectTagCarrier tag)
	{
		m_tagList->addTag(tag);
	}

	void GameObject::removeGameobjectTag(GameObjectTagCarrier tag)
	{
		m_tagList->removeTag(tag);
	}

	bool GameObject::containGameobjectTag(GameObjectTagCarrier tag) const
	{
		return m_tagList->contain(tag);
	}

	void GameObject::runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		m_componentList->runHandleMessageAll(type, attachment);
	}

	void GameObject::runAfterChangeParentAll(const GameObjectPtr& beforParent)
	{
		m_componentList->runAfterChangeParentAll(beforParent);
	}

	void GameObject::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
		m_componentList->runOnCollisionEnterAll(other);
	}

	void GameObject::runOnCollisionStayAll(const GameObjectPtr& other)
	{
		m_componentList->runOnCollisionStayAll(other);
	}

	void GameObject::runOnCollisionExitAll(const GameObjectPtr& other)
	{
		m_componentList->runOnCollisionExitAll(other);
	}

	const GameObjectPtr& GameObject::getParent() const
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		return m_parentChildManager->getParent();
	}

	void GameObject::setParent(const GameObjectPtr& parent)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		m_parentChildManager->setParent(parent);
	}

	const std::forward_list<GameObjectPtr>& GameObject::getChildren() const
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		return m_parentChildManager->getChildren();
	}

	GameObjectPtr GameObject::findChildWithTag(GameObjectTagCarrier tag) const
	{
		return m_parentChildManager->findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> GameObject::findChildrenWithTag(GameObjectTagCarrier tag) const
	{
		return m_parentChildManager->findGameObjectsWithTag(tag);
	}

	void GameObject::addChild(const GameObjectPtr& child)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		// 追加する前の子要素の親要素を取得
		const GameObjectPtr& beforeChildParent = child->getParent();

		// もう引数のGameObjectが自身の子要素だったら何もしない
		if (beforeChildParent.isSame(GameObjectPtr(weak_from_this()))) return;

		// 既に親要素を持っていたら
		if (!beforeChildParent.expired())
		{
			// その親要素から追加する前の子要素を削除する
			beforeChildParent->m_parentChildManager->removeChild(child);
		}
		// 自身の親子関係管理コンポーネントに新たな子要素を追加する
		m_parentChildManager->addChild(child);

		// 追加する子供の親子関係管理コンポーネントの親要素を更新する
		child->m_parentChildManager->setParent(GameObjectPtr(weak_from_this()));

		// 追加する子供の親変更時関数を呼ぶ
		child->m_componentList->runAfterChangeParentAll(beforeChildParent);
	}

	void GameObject::removeChild(const GameObjectPtr& child)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		// 追加する前の子要素の親要素を取得
		const GameObjectPtr& beforeChildParent = child->getParent();

		// 親要素を持っていない or 自身ではない親を持っていたら 何もしない
		if (beforeChildParent.expired() || !beforeChildParent.isSame(GameObjectPtr(weak_from_this()))) return;

		// 削除したい子要素の親子関係管理コンポーネントの親要素を更新する
		child->m_parentChildManager->setParent(GameObjectPtr());

		// 自身の親子関係管理コンポーネントから削除したい子要素を削除する
		m_parentChildManager->removeChild(child);

		// 追加する子供の親変更時関数を呼ぶ
		child->m_componentList->runAfterChangeParentAll(GameObjectPtr(weak_from_this()));
	}

	void GameObject::sendMessage(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		// 自身のメッセージ受信処理を呼ぶ
		runHandleMessageAll(type, attachment);

#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		// 自身の子要素のメッセージ受信処理を呼ぶ
		m_parentChildManager->sendMessage(type, attachment);
	}

	void GameObject::setupStateMachine(const StateMachineListInitParam& initParam)
	{
		// 現在のステートを管理するコンポーネントを作る
		m_stateTypeList		= createComponent<CurStateTypeList>();

		// 引数分のステートのステートマシンを作る
		m_stateMachineList	= std::make_unique<StateMachineList>(initParam, GameObjectPtr(weak_from_this()), m_componentList);
	}

	void GameObject::stateEnable(StateTypeCarrier stateType)
	{
		m_stateTypeList->stateEnable(stateType);
	}

	void GameObject::stateDisable(StateTypeCarrier stateType)
	{
		m_stateTypeList->stateDisable(stateType);
	}

	void GameObject::childStateEnable(const StateTypeHierarchy& targetState)
	{
		for (const auto& stateType : m_stateMachineList->getChildNode(targetState).list)
		{
			m_stateTypeList->stateEnable(stateType);
		}
	}

	void GameObject::childStateDisable(const StateTypeHierarchy& targetState)
	{
		for (const auto& stateType : m_stateMachineList->getChildNode(targetState).list)
		{
			m_stateTypeList->stateDisable(stateType);
		}
	}

	void GameObject::clearState()
	{
		m_stateTypeList->clearState();
	}

	bool GameObject::containState(StateTypeCarrier stateType)
	{
		return m_stateTypeList->contain(stateType);
	}

	void GameObject::addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child)
	{
		m_stateMachineList->addChild(targetState, child);
	}

	ComponentPtr<StateChangeTimer> GameObject::createStateChangeTimer(const StateTypeHierarchy& targetState, float stateChangeTimeSec, const StateTypeList& enableStates, const StateTypeList& disableStates)
	{
		auto createdComponent = DX12GameManager::createComponent<StateChangeTimer>(GameObjectPtr(weak_from_this()), stateChangeTimeSec, enableStates, disableStates);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		setComponentToStateMachine(targetState, ComponentBasePtr(createdComponent));
		return m_componentList->add(createdComponent);
	}

	ComponentPtr<MessageStateChanger> GameObject::createMessageStateChanger(const StateTypeHierarchy& targetState, MessageTypeCarrier messageType, const StateTypeList& enableStates, const StateTypeList& disableStates)
	{
		auto createdComponent = DX12GameManager::createComponent<MessageStateChanger>(GameObjectPtr(weak_from_this()), messageType, enableStates, disableStates);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		setComponentToStateMachine(targetState, ComponentBasePtr(createdComponent));
		return m_componentList->add(createdComponent);
	}

	void GameObject::setComponentToStateMachine(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr)
	{
		m_stateMachineList->addComponent(targetState, componentPtr);
	}
}