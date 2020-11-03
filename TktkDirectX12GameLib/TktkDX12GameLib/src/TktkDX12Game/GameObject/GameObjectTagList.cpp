#include "TktkDX12Game/GameObject/GameObjectTagList.h"

namespace tktk
{
	void GameObjectTagList::addTag(GameObjectTagCarrier tag)
	{
		m_tags.insert(tag);
	}

	void GameObjectTagList::removeTag(GameObjectTagCarrier tag)
	{
		m_tags.erase(tag);
	}

	bool GameObjectTagList::contain(GameObjectTagCarrier tag) const
	{
		return (m_tags.find(tag) != std::end(m_tags));
	}
}