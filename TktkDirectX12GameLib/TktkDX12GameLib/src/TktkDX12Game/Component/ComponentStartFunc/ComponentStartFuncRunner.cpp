#include "TktkDX12Game/Component/ComponentStartFunc/ComponentStartFuncRunner.h"

#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentStartFuncRunner::runStart()
	{
		// ��������start�֐������s���Ă��邩�A���g������ł��邩�A��A�N�e�B�u��ԂɂȂ��Ă����牽�����Ȃ�
		if (m_afterRun || m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// start�֐����Ă�
		m_vtablePtr->runStart(m_selfPtr);

		// start�֐����s��t���O�𗧂Ă�
		m_afterRun = true;
	}

	bool ComponentStartFuncRunner::isDead() const
	{
		// start�֐����s��t���O�������Ă��Ă����S�����Ԃ�
		return (m_afterRun || m_selfPtr.isDead());
	}
}