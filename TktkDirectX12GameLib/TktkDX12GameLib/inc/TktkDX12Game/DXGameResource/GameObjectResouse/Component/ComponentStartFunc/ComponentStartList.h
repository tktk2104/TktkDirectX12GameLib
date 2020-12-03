#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

/* std::forward_list */
#include <forward_list>

namespace tktk
{
	class ComponentStartFuncRunner;
	class ComponentBasePtr;
	struct ComponentStartFuncVTable;

	// �R���|�[�l���g�́ustart�v�֐������s���郊�X�g
	class ComponentStartList
	{
	public:

		ComponentStartList();
		~ComponentStartList();

	public:

		// ���g�̃R���e�i�ɒǉ�����
		void add(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr);

		// �ustart�v�֐����Ă�
		void runStartFunc();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���Ɂustart�v�֐����Ă΂ꂽ���A���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartFuncRunner> m_startList;
		std::forward_list<ComponentStartFuncRunner> m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_SATRT_LIST_H_