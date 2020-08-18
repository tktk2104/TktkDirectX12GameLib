#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ChildList.h"

#include <algorithm>
#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	void ChildList::addChild(const GameObjectPtr& child)
	{
		m_newComponentList.push_front(child);
	}

	const std::forward_list<GameObjectPtr>& ChildList::getChildren() const
	{
		return m_childList;
	}

	GameObjectPtr ChildList::findGameObjectWithTag(int tag) const
	{
		for (const auto& node : m_childList)
		{
			if (node->containGameobjectTag(tag)) return node;

			// 孫要素で再起する
			auto findGrandchildResult = node->findChildWithTag(tag);

			// 孫要素で対象となるゲームオブジェクトを見つけたらそれを返す
			if (!findGrandchildResult.expired()) return findGrandchildResult;
		}
		return GameObjectPtr();
	}

	std::forward_list<GameObjectPtr> ChildList::findGameObjectsWithTag(int tag) const
	{
		std::forward_list<GameObjectPtr> result;

		for (const auto& node : m_childList)
		{
			if (node->containGameobjectTag(tag))
			{
				result.push_front(node);
			}

			// 孫要素で再起した結果を検索結果リストに追加する
			result.splice_after(result.before_begin(), std::move(node->findChildrenWithTag(tag)));
		}
		return result;
	}

	void ChildList::updateContainer()
	{
		// 前フレームで追加されたゲームオブジェクトをメインリストに移動する
		m_childList.splice_after(m_childList.before_begin(), std::move(m_newComponentList));

		// 死んでいるゲームオブジェクトをメインリストから削除する
		m_childList.remove_if([](const GameObjectPtr& node) { return node.expired(); });
	}

	void ChildList::remove(const GameObjectPtr& gameObject)
	{
		m_childList.remove_if([gameObject](const GameObjectPtr& node) { return (node.isSame(gameObject)); });
	}

	void ChildList::destroyAll()
	{
		for (const auto& node : m_childList)
		{
			node->destroy();
		}
	}

	void ChildList::sendMessage(unsigned int messageId, const MessageAttachment& value)
	{
		for (const auto& node : m_childList)
		{
			node->sendMessage(messageId, value);
		}
	}
}