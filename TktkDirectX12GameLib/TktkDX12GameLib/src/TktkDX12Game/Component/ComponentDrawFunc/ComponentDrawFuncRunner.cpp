#include "TktkDX12Game/Component/ComponentDrawFunc/ComponentDrawFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentDrawFuncRunner::runDrawFunc() const
	{
		// ���g������ł��邩�A��A�N�e�B�u��ԂɂȂ��Ă����牽�����Ȃ�
		if (m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// �`��֐����Ă�
		m_vtablePtr->runDraw(m_selfPtr);
	}

	bool ComponentDrawFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}
}