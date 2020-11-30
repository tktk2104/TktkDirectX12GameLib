#ifndef COMPONENT_MAIN_LIST_H_
#define COMPONENT_MAIN_LIST_H_

/* std::shared_ptr, std::weak_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* std::multimap */
#include <map>

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include "../PriorityList/ComponentRunFuncPriorityList.h"

namespace tktk
{
	struct ComponentListVTable;
	class ComponentTypeList;
	class ComponentBase;

	class ComponentMainList
	{
	public:

		ComponentMainList();
		~ComponentMainList();

	public:

		// �R���|�[�l���g��ǉ�����
		void addComponent(std::type_index type, ComponentListVTable* vtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

		// �����̌^�̃R���|�[�l���g�̍X�V�D��x��ݒ肷��
		void addRunFuncPriority(std::type_index type, float priority);

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// �A�N�e�B�u��Ԃ̔�����s��
		void activeChangeCheck();

		// �X�V�������Ă�
		void update();

		// �Փ˔��蒼�O�������Ă�
		void runBeforeCollide();

		// �Փ˔���㏈�����Ă�
		void runAfterCollide();

		// ���񂾃R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		ComponentRunFuncPriorityList												m_priorityList;		// �R���|�[�l���g�̍X�V�����̌Ăяo�������Ǘ����郊�X�g
		std::multimap		<float,				std::shared_ptr<ComponentTypeList>>	m_mainMap;			// �R���|�[�l���g�����񂷂邽�߂̃}�b�v
		std::unordered_map	<std::type_index,	std::weak_ptr<ComponentTypeList>>	m_addComponentMap;	// �R���|�[�l���g��ǉ����邽�߂̃}�b�v
	};
}
#endif // !COMPONENT_MAIN_LIST_H_