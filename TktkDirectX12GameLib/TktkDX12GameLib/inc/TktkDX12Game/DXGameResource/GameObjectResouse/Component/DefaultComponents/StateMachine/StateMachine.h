#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

/* std::forward_list */
#include <forward_list>

/* baseClass */
#include "../../ComponentBase.h"

/* class member */
#include "Structs/StateTypeCarrier.h"

namespace tktk
{
	/* class member */
	class GameObjectPtr;
	class ComponentBasePtr;
	class CurStateTypeList;

	// �X�e�[�g�}�V�[���R���|�[�l���g
	// �y�O��R���|�[�l���g�FCurStateTypeList�z
	class StateMachine
		: public ComponentBase
	{
	public:

		explicit StateMachine(StateTypeCarrier stateType);

	public:

		void onDisable();
		void start();
		void afterCollide();

	public:

		// ���̃X�e�[�g�Ɏq�v�f��ǉ�����
		void addChild(const GameObjectPtr& child);

		// ���̃X�e�[�g����q�v�f���폜����
		void removeChild(const GameObjectPtr& child);

		// ���̃X�e�[�g�ɃR���|�[�l���g��ǉ�����
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// ���g�̃X�e�[�g�̎��
		StateTypeCarrier m_selfStateType;

		// ���g�̌��݂̃X�e�[�g�̎�ނ̃R���|�[�l���g
		ComponentPtr<CurStateTypeList> m_curStateTypeList;

		// ���̃X�e�[�g���Ǘ�����GameObject�̃R���e�i
		std::forward_list<GameObjectPtr> m_gameObjectList;

		// ���̃X�e�[�g���Ǘ�����R���|�[�l���g�̃R���e�i
		std::forward_list<ComponentBasePtr> m_componentList;
	};
}
#endif // !STATE_MACHINE_H_