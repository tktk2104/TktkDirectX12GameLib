#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

#include <vector>
#include <forward_list>
#include <unordered_map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasIsCollideChecker.h>
#include "ComponentCollisionFuncRunner.h"

namespace tktk
{
	// �w��̃N���X���ϐ���isCollide�֐��������Ă��邩���肷��e���v���[�g���^�̃G�C���A�X�e���v���[�g
	template <class ComponentType>
	using has_isCollide = std::enable_if_t<has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*;
	template <class ComponentType>
	using not_has_isCollide = std::enable_if_t<!has_isCollide_checker<ComponentType*, bool, const tktk::ComponentBasePtr&>::value>*;


	// �R���|�[�l���g�̏Փ˔�����s�����X�g
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList() = default;

	public:

		// �Փ˔���֐������s����
		void runCollisionFunc();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�Ɉړ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(int firstGroup, int secondGroup);

	public:

		// �����̃R���|�[�l���g�̌^���uisCollide()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, has_isCollide<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_isCollide<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::vector<std::pair<int, int>>								m_collisionGroupPairArray;
		std::unordered_multimap<int, ComponentCollisionFuncRunner>		m_collisionList;
		std::forward_list<std::pair<int, ComponentCollisionFuncRunner>>	m_nextFrameAddNodeList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���uisCollide()�v�֐��������Ă����玟�t���[���Ń��C�����X�g�ɒǉ����邽�߂̈ꎞ���X�g�ɒǉ�����
	template<class ComponentType, has_isCollide<ComponentType>>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr.lock()->getCollisionGroup(), componentPtr);
	}
	template<class ComponentType, not_has_isCollide<ComponentType>>
	inline void ComponentCollisionList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_COLLISION_LIST_H_