#ifndef COMPONENT_START_RUNNER_H_
#define COMPONENT_START_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentStartFuncVTable;

	// �R���|�[�l���g�́ustart�v�֐����ĂԂ��߂̃N���X
	class ComponentStartFuncRunner
	{
	public:

		ComponentStartFuncRunner(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr);

	public:

		// �ustart�v�֐����Ă�
		void runStart();

		// �R���|�[�l���g�̎��S�t���O���擾����
		bool isDead() const;

	private:

		bool						m_afterRun{ false };
		ComponentStartFuncVTable*	m_vtablePtr;
		ComponentBasePtr			m_selfPtr;
	};
}
#endif // !COMPONENT_START_RUNNER_H_