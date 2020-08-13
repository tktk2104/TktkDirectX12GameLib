#include "TktkDX12Game/Component/ComponentCollisionFunc/ComponentCollisionList.h"

namespace tktk
{
	void ComponentCollisionList::runCollisionFunc()
	{
		for (auto& node : m_collisionList)
		{
			node.second.updateHitObjectList();
		}

		for (const auto& node : m_collisionGroupPairArray)
		{
			auto firstGroup = m_collisionList.equal_range(node.first);
			auto secondGroup = m_collisionList.equal_range(node.second);

			for (auto firstItr = firstGroup.first; firstItr != firstGroup.second; firstItr++)
			{
				for (auto secondItr = secondGroup.first; secondItr != secondGroup.second; secondItr++)
				{
					(*firstItr).second.runCollideFunc((*secondItr).second);
				}
			}
		}
	}

	void ComponentCollisionList::moveNewComponent()
	{
		for (auto& node : m_newComponentList)
		{
			m_collisionList.insert(node);
		}

		m_newComponentList.clear();
	}

	void ComponentCollisionList::removeDeadComponent()
	{
		for (auto itr = std::begin(m_collisionList); itr != std::end(m_collisionList);)
		{
			if ((*itr).second.isDead())
			{
				itr = m_collisionList.erase(itr);
				continue;
			}
			++itr;
		}
	}

	void ComponentCollisionList::addCollisionGroup(int firstGroup, int secondGroup)
	{
		m_collisionGroupPairArray.push_back(std::make_pair(firstGroup, secondGroup));
	}
	
}