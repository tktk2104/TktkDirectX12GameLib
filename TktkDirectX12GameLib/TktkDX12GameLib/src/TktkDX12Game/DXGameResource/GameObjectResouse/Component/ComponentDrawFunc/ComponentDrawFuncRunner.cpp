#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentDrawFunc/ComponentDrawFuncRunner.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	ComponentDrawFuncRunner::ComponentDrawFuncRunner(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr)
		: m_vtablePtr(vtablePtr)
		, m_selfPtr(componentPtr)
	{
	}

	void ComponentDrawFuncRunner::runDrawFunc() const
	{
		// 自身が死んでいるか、非アクティブ状態になっていたら何もしない
		if (m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// 描画関数を呼ぶ
		m_vtablePtr->draw(m_selfPtr);
	}

	bool ComponentDrawFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}
}