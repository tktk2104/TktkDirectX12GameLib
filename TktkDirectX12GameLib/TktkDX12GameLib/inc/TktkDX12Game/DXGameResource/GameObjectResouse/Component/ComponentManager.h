#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* funcUseType */
#include "ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "ComponentBasePtr.h"

namespace tktk
{
	class ComponentMainList;
	class ComponentStartList;
	class ComponentDrawList;
	class ComponentCollisionList;
	struct ComponentListVTable;
	struct ComponentVTableBundle;
	class ComponentBase;

	// �S�ẴR���|�[�l���g���Ǘ�����}�l�[�W���[�N���X
	class ComponentManager
	{
	public:

		ComponentManager();
		~ComponentManager();

	public:

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// �R���|�[�l���g�̍X�V����
		void update();

		// ���񂾃R���|�[�l���g���폜����
		void removeDeadComponent();

		// �R���|�[�l���g�̕`�揈��
		void draw();

	public:

		// �R���|�[�l���g�̌^���Ƃ̍X�V�D��x��ݒ肷��
		// ���f�t�H���g�i0.0f�j�Œl�����������A�������s�����
		void addRunFuncPriority(std::type_index type, float priority);

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

		// �����̃R���|�[�l���g��ǉ�����
		ComponentBasePtr addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr);

	private:

		std::unique_ptr<ComponentMainList>		m_componentMainList;
		std::unique_ptr<ComponentStartList>		m_componentStartList;
		std::unique_ptr<ComponentDrawList>		m_componentDrawList;
		std::unique_ptr<ComponentCollisionList> m_componentCollisionList;
	};
}
#endif // !COMPONENT_MANAGER_H_