#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentGameObjectFunc/GameObjectComponentList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentGameObjectFunc/ComponentGameObjectFuncRunner.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	// コンストラクタを非インライン化する
	GameObjectComponentList::GameObjectComponentList() = default;

	// デストラクタを非インライン化する
	GameObjectComponentList::~GameObjectComponentList() = default;

	void GameObjectComponentList::add(const ComponentBasePtr& componentPtr, ComponentGameObjectFuncVTable* vtablePtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr, vtablePtr);
	}

	ComponentBasePtr GameObjectComponentList::find(std::type_index type) const
	{
		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast(type))
			{
				return gameObjectPtr;
			}
		}
		return ComponentBasePtr();
	}

	std::forward_list<ComponentBasePtr> GameObjectComponentList::findAll(std::type_index type) const
	{
		std::forward_list<ComponentBasePtr> result;

		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast(type))
			{
				result.push_front(gameObjectPtr);
			}
		}
		return result;
	}

	void GameObjectComponentList::runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment) const
	{
		for (const auto& component : m_componentList)
		{
			component.runHandleMessage(type, attachment);
		}
	}

	void GameObjectComponentList::runAfterChangeParentAll(const GameObjectPtr& beforParent) const
	{
		for (const auto& component : m_componentList)
		{
			component.runAfterChangeParent(beforParent);
		}
	}

	void GameObjectComponentList::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionEnter(other);
		}
	}

	void GameObjectComponentList::runOnCollisionStayAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionStay(other);
		}
	}

	void GameObjectComponentList::runOnCollisionExitAll(const GameObjectPtr& other)
	{
		// 現在のフレームで既に衝突処理が呼ばれた組み合わせの場合、何もしない
		for (const auto& curFrameHitObject : m_curFrameHitObjectList)
		{
			if (curFrameHitObject.isSame(other)) return;
		}

		// 現在のフレームで衝突処理を行ったオブジェクトリストに衝突相手のオブジェクトポインタを追加する
		m_curFrameHitObjectList.push_front(other);

		for (const auto& component : m_componentList)
		{
			component.runOnCollisionExit(other);
		}
	}

	void GameObjectComponentList::clearHitObjectList()
	{
		m_curFrameHitObjectList.clear();
	}

	void GameObjectComponentList::destroyAll() const
	{
		for (const auto& component : m_nextFrameAddNodeList)
		{
			component.destroy();
		}

		for (const auto& component : m_componentList)
		{
			component.destroy();
		}
	}

	void GameObjectComponentList::movePreFrameAddedNode()
	{
		// メインリストに移動する情報が入ったリストの要素をメインリストに移動
		for (const auto& node : m_nextFrameAddNodeList)
		{
			m_componentList.push_front(node);
		}

		// コピー元のコンテナは削除
		m_nextFrameAddNodeList.clear();
	}

	void GameObjectComponentList::removeDeadComponent()
	{
		// 死亡フラグの立ったコンポーネントをリストから削除する
		m_componentList.remove_if([](const auto& node) { return node.isDead(); });
	}
}