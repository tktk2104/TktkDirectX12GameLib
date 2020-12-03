#ifndef COMPONENT_TYPE_LIST_H_
#define COMPONENT_TYPE_LIST_H_

/* std::shared_ptr */
#include <memory>

/* std::forward_list */
#include <forward_list>

namespace tktk
{
	struct ComponentListVTable;
	class ComponentBase;

	// �P��ނ̃R���|�[�l���g���Ǘ����郊�X�g�N���X
	class ComponentTypeList
	{
	public:

		explicit ComponentTypeList(ComponentListVTable* vtablePtr);

	public:

		// �R���|�[�l���g��ǉ�����
		void addComponent(const std::shared_ptr<ComponentBase>& componentPtr);

		// ���g���Ǘ�����R���|�[�l���g�����񂵁A�A�N�e�B�u�t���O���O�t���[���ƕς���Ă�����uonEnable()�v�������́uonDisable()�v�֐��̎��s�����݂�
		void activeChangeCheck();

		// ���g���Ǘ�����R���|�[�l���g�̌^���uupdate()�v�֐��������Ă����炻����S�Ď��s����
		void runUpdate();

		// ���g���Ǘ�����R���|�[�l���g�̌^���ubeforeCollide�v�֐��������Ă����炻����S�Ď��s����
		void runBeforeCollide();

		// ���g���Ǘ�����R���|�[�l���g�̌^���uafterCollide�v�֐��������Ă����炻����S�Ď��s����
		void runAfterCollide();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void moveNewComponent();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		ComponentListVTable*								m_vtablePtr;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_mainList;
		std::forward_list<std::shared_ptr<ComponentBase>>	m_newComponentList;
	};
}
#endif // !COMPONENT_TYPE_LIST_H_