#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

/* std::forward_list */
#include <forward_list>

/* std::multimap */
#include <map>

namespace tktk
{
	/* funcUseType */
	class ComponentBasePtr;
	struct ComponentDrawFuncVTable;

	/* class member */
	class ComponentDrawFuncRunner;

	// �R���|�[�l���g�̕`�揈�����s�����X�g
	class ComponentDrawList
	{
	public:

		ComponentDrawList();
		~ComponentDrawList();

	public:

		// ���g�̃R���e�i�ɒǉ�����
		void add(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr);

		// �`��D��x���Łudraw�v�֐����Ă�
		void runDrawFunc() const;

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::multimap<float, ComponentDrawFuncRunner>					m_drawList;
		std::forward_list<std::pair<float, ComponentDrawFuncRunner>>	m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_DRAW_LIST_H_