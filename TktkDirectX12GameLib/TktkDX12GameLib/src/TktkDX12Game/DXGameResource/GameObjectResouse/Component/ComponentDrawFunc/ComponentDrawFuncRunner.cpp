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
		// ���g������ł��邩�A��A�N�e�B�u��ԂɂȂ��Ă����牽�����Ȃ�
		if (m_selfPtr.isDead() || !m_selfPtr->isActive()) return;

		// �`��֐����Ă�
		m_vtablePtr->draw(m_selfPtr);
	}

	bool ComponentDrawFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}
}