#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObjectResouse.h"

#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObjectManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	// コンストラクタを非インライン化する
	GameObjectResouse::GameObjectResouse()
	{
		m_gameObjectManager	= std::make_unique<GameObjectManager>();
		m_componentManager	= std::make_unique<ComponentManager>();
	}

	// デストラクタを非インライン化する
	GameObjectResouse::~GameObjectResouse() = default;

	void GameObjectResouse::movePreFrameAddedNode()
	{
		m_gameObjectManager->movePreFrameAddedNode();
		m_componentManager->movePreFrameAddedNode();
	}

	void GameObjectResouse::update()
	{
		m_gameObjectManager->update();
		m_componentManager->update();
	}

	void GameObjectResouse::removeDeadInstance()
	{
		m_gameObjectManager->removeDeadObject();
		m_componentManager->removeDeadComponent();
	}

	void GameObjectResouse::draw()
	{
		m_componentManager->draw();
	}

	void GameObjectResouse::runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment)
	{
		m_gameObjectManager->runHandleMessageAll(type, attachment);
	}

	GameObjectPtr GameObjectResouse::createGameObject()
	{
		return m_gameObjectManager->createGameObject();
	}

	GameObjectPtr GameObjectResouse::findGameObjectWithTag(GameObjectTagCarrier tag) const
	{
		return m_gameObjectManager->findGameObjectWithTag(tag);
	}

	std::forward_list<GameObjectPtr> GameObjectResouse::findGameObjectsWithTag(GameObjectTagCarrier tag) const
	{
		return m_gameObjectManager->findGameObjectsWithTag(tag);
	}

	void GameObjectResouse::destroyGameObjectsWithTag(GameObjectTagCarrier tag)
	{
		m_gameObjectManager->destroyGameObjectsWithTag(tag);
	}

	void GameObjectResouse::addRunFuncPriority(std::type_index type, float priority)
	{
		m_componentManager->addRunFuncPriority(type, priority);
	}

	void GameObjectResouse::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		m_componentManager->addCollisionGroup(firstGroup, secondGroup);
	}

	ComponentBasePtr GameObjectResouse::addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const GameObjectPtr& user, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		// コンポーネントを管理リストに追加する
		auto createdComponent = m_componentManager->addComponent(type, vtablePtrBundle, listVtablePtr, componentPtr);

		// コンポーネントに所持者オブジェクトを登録する
		createdComponent->setUser(user);

		// 「awake」 関数を呼ぶ
		awake_runner<void>::checkAndRun(createdComponent);

		// 作ったコンポーネントのポインタを返す
		return createdComponent;
	}
}