#ifndef COMPONENT_COLLISION_FUNC_RUNNER_H_
#define COMPONENT_COLLISION_FUNC_RUNNER_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include "../ComponentBasePtr.h"

namespace tktk
{
	struct ComponentCollisionFuncVTable;

	// �R���|�[�l���g�̏Փ˔���֐����ĂԂ��߂̃N���X
	class ComponentCollisionFuncRunner
	{
	public:

		ComponentCollisionFuncRunner(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr);

	public:

		// �O�t���[���ŏՓ˂����I�u�W�F�N�g���Ǘ����郊�X�g���X�V����
		void updateHitObjectList();

		// �Փ˔��菈�����s��
		void runCollideFunc(const ComponentCollisionFuncRunner& other);

		// �R���|�[�l���g�����S���Ă��邩���擾����
		bool isDead() const;

	private:

		// �Փˑ���̏��
		struct HitObject
		{
			HitObject(ComponentCollisionFuncVTable* vtablePtr, ComponentBasePtr selfPtr)
				: vtablePtr(vtablePtr)
				, selfPtr(selfPtr) {}

			ComponentCollisionFuncVTable*	vtablePtr;
			ComponentBasePtr				selfPtr;
		};

	private:

		ComponentCollisionFuncVTable*	m_vtablePtr;
		ComponentBasePtr				m_selfPtr;

		// ���݂̃t���[���̏Փˑ�����
		std::forward_list<HitObject> m_curHitObjectList;

		// �P�O�̃t���[���̏Փˑ�����
		std::forward_list<HitObject> m_preHitObjectList;
	};
}
#endif // !COMPONENT_COLLISION_FUNC_RUNNER_H_