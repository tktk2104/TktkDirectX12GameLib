#include "TktkDX12Game/GameObject/GameObjectTagList.h"

namespace tktk
{
	void GameObjectTagList::addTag(unsigned int tag)
	{
		m_tagList.insert(tag);
	}

	void GameObjectTagList::removeTag(unsigned int tag)
	{
		m_tagList.erase(tag);
	}

	bool GameObjectTagList::contain(unsigned int tag) const
	{
		return (m_tagList.find(tag) != std::end(m_tagList));
	}
}