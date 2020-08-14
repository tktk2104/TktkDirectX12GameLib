#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentDrawFuncRunner::runDrawFunc() const
	{
		// 自身が死んでいるか、非アクティブ状態になっていたら何もしない
		if (m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// 描画関数を呼ぶ
		m_vtablePtr->runDraw(m_selfPtr);
	}

	bool ComponentDrawFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}
}