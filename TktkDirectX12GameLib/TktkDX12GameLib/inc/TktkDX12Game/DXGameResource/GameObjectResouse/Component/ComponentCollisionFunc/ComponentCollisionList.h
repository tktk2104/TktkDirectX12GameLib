#ifndef COMPONENT_COLLISION_LIST_H_
#define COMPONENT_COLLISION_LIST_H_

/* std::vector */
#include <vector>

/* std::forward_list */
#include <forward_list>

/* std::unordered_multimap */
#include <unordered_map>

/* class member */
#include "CollisionGroupTypeCarrier.h"

namespace tktk
{
	class ComponentCollisionFuncRunner;
	class ComponentBasePtr;
	struct ComponentCollisionFuncVTable;

	// �R���|�[�l���g�̏Փ˔�����s�����X�g
	class ComponentCollisionList
	{
	public:

		ComponentCollisionList();
		~ComponentCollisionList();

	public:

		// �Փ˔���֐������s����
		void runCollisionFunc();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�Ɉړ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

		// �Փ˔���̑g�ݍ��킹��ǉ�����
		void addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup);

	public:

		void add(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr);

	private:

		std::vector<std::pair<CollisionGroupTypeCarrier, CollisionGroupTypeCarrier>>			m_collisionGroupPairArray;
		std::unordered_multimap<CollisionGroupTypeCarrier, ComponentCollisionFuncRunner>		m_collisionList;
		std::forward_list<std::pair<CollisionGroupTypeCarrier, ComponentCollisionFuncRunner>>	m_nextFrameAddNodeList;
	};
}
#endif // !COMPONENT_COLLISION_LIST_H_