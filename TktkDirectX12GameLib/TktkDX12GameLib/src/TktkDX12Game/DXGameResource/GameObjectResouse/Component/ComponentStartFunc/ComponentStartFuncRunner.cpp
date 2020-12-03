#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentStartFunc/ComponentStartFuncRunner.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	ComponentStartFuncRunner::ComponentStartFuncRunner(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr)
		: m_vtablePtr(vtablePtr)
		, m_selfPtr(componentPtr)
	{
	}

	void ComponentStartFuncRunner::runStart()
	{
		// もう既にstart関数を実行しているか、自身が死んでいるか、非アクティブ状態になっていたら何もしない
		if (m_afterRun || m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// start関数を呼ぶ
		m_vtablePtr->start(m_selfPtr);

		// start関数実行後フラグを立てる
		m_afterRun = true;
	}

	bool ComponentStartFuncRunner::isDead() const
	{
		// start関数実行後フラグが立っていても死亡判定を返す
		return (m_afterRun || m_selfPtr.isDead());
	}
}