#include "TktkDX12Game/GameObject/GameObjectTagList.h"

namespace tktk
{
	void GameObjectTagList::addTag(int tag)
	{
		m_tagList.insert(tag);
	}

	void GameObjectTagList::removeTag(int tag)
	{
		m_tagList.erase(tag);
	}

	bool GameObjectTagList::contain(int tag) const
	{
		return (m_tagList.find(tag) != std::end(m_tagList));
	}
}