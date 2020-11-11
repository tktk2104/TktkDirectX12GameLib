#ifndef COMPONENT_DRAW_RUNNER_H_
#define COMPONENT_DRAW_RUNNER_H_

/* class member */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentDrawFuncVTable;

	// �R���|�[�l���g�̕`��֐����ĂԂ��߂̃N���X
	class ComponentDrawFuncRunner
	{
	public:

		ComponentDrawFuncRunner(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr);

	public:

		// �`�揈�����s��
		void runDrawFunc() const;

		// �R���|�[�l���g�����S���Ă��邩���擾����
		bool isDead() const;

	private:

		ComponentDrawFuncVTable*	m_vtablePtr;
		ComponentBasePtr			m_selfPtr;
	};
}
#endif // !COMPONENT_DRAW_RUNNER_H_