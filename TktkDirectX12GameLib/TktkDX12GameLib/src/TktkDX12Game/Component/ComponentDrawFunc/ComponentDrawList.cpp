#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawList.h"

namespace tktk
{
	void ComponentDrawList::runDraw()
	{
		for (auto& node : m_drawList)
		{
			node.second.runDraw();
		}
	}

	void ComponentDrawList::moveNewComponent()
	{
		for (auto& node : m_newComponentList)
		{
			m_drawList.insert(node);
		}

		m_newComponentList.clear();
	}

	void ComponentDrawList::removeDeadComponent()
	{
		for (auto itr = std::begin(m_drawList); itr != std::end(m_drawList);)
		{
			if ((*itr).second.isDead())
			{
				itr = m_drawList.erase(itr);
				continue;
			}
			++itr;
		}
	}
}