#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentManager.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentMainList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentStartFunc/ComponentStartList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentDrawFunc/ComponentDrawList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"

namespace tktk
{
	// コンストラクタを非インライン化する
	ComponentManager::ComponentManager()
	{
		m_componentMainList			= std::make_unique<ComponentMainList>();
		m_componentStartList		= std::make_unique<ComponentStartList>();
		m_componentDrawList			= std::make_unique<ComponentDrawList>();
		m_componentCollisionList	= std::make_unique<ComponentCollisionList>();
	}

	// デストラクタを非インライン化する
	ComponentManager::~ComponentManager() = default;

	void ComponentManager::movePreFrameAddedNode()
	{
		// 前フレームに追加されたコンポーネントをメインリストに追加する
		m_componentMainList->movePreFrameAddedNode();
		m_componentStartList->movePreFrameAddedNode();
		m_componentDrawList->movePreFrameAddedNode();
		m_componentCollisionList->movePreFrameAddedNode();
	}

	void ComponentManager::update()
	{
		// アクティブ状態の判定を行う
		m_componentMainList->activeChangeCheck();

		// 「start」関数呼び出し処理
		m_componentStartList->runStartFunc();
		
		// 更新処理を呼ぶ
		m_componentMainList->update();

		// 衝突判定直前処理を呼ぶ
		m_componentMainList->runBeforeCollide();

		// 衝突判定系関数呼び出し処理
		m_componentCollisionList->runCollisionFunc();

		// 衝突判定後処理を呼ぶ
		m_componentMainList->runAfterCollide();
	}

	void ComponentManager::removeDeadComponent()
	{
		// 死んだコンポーネントを削除する
		m_componentMainList->removeDeadComponent();

		// 衝突判定リストが管理しているコンポーネントポインタの生存確認
		m_componentCollisionList->removeDeadComponent();

		// 描画リストが管理しているコンポーネントポインタの生存確認
		m_componentDrawList->removeDeadComponent();

		// 既に「start」関数が呼ばれたか、死亡フラグが立っているコンポーネントを削除する
		m_componentStartList->removeDeadComponent();
	}

	void ComponentManager::draw()
	{
		// 「draw()」関数呼び出し処理
		m_componentDrawList->runDrawFunc();
	}

	void ComponentManager::addRunFuncPriority(std::type_index type, float priority)
	{
		m_componentMainList->addRunFuncPriority(type, priority);
	}

	void ComponentManager::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		// 衝突判定の組み合わせを追加
		m_componentCollisionList->addCollisionGroup(firstGroup, secondGroup);
	}

	ComponentBasePtr ComponentManager::addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		m_componentMainList->addComponent(type, listVtablePtr, componentPtr);

		ComponentBasePtr createdPtr = ComponentBasePtr(type, componentPtr);

		// 各種関数呼び出し処理リストにそのweak_ptrを渡す
		m_componentStartList->add(createdPtr, vtablePtrBundle->startFuncVTable);
		m_componentCollisionList->add(createdPtr, vtablePtrBundle->collisionFuncVTable);
		m_componentDrawList->add(createdPtr, vtablePtrBundle->drawFuncVTable);

		// 作ったコンポーネントのweak_ptrを返して終了
		return createdPtr;
	}
}