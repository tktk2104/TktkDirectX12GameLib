#include "TktkDX12Game/Component/ComponentStartFunc/ComponentStartFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentStartFuncRunner::runStart()
	{
		// もう既にstart関数を実行しているか、自身が死んでいるか、非アクティブ状態になっていたら何もしない
		if (m_afterRun || m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// start関数を呼ぶ
		m_vtablePtr->runStart(m_selfPtr);

		// start関数実行後フラグを立てる
		m_afterRun = true;
	}

	bool ComponentStartFuncRunner::isDead() const
	{
		// start関数実行後フラグが立っていても死亡判定を返す
		return (m_afterRun || m_selfPtr.isDead());
	}
}