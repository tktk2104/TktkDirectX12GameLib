#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionFuncRunner.h"

namespace tktk
{
	// �R���X�g���N�^���C�����C��������
	ComponentCollisionList::ComponentCollisionList() = default;

	// �f�X�g���N�^���C�����C��������
	ComponentCollisionList::~ComponentCollisionList() = default;

	void ComponentCollisionList::runCollisionFunc()
	{
		// �O�t���[���ŏՓ˂�������̏����X�V����
		// ���R���e�i�̗v�f��ύX���鏈���ȈׁA��const
		for (auto& collisionFuncRunner : m_collisionList)
		{
			collisionFuncRunner.second.updateHitObjectList();
		}

		// �Փ˔���̑g�ݍ��킹�����񂷂�
		for (const auto& collisionGroupPair : m_collisionGroupPairArray)
		{
			// �P�ڂ̏Փ˔���O���[�v�͈̔͂�\���C�e���[�^�y�A
			auto firstGroup = m_collisionList.equal_range(collisionGroupPair.first);

			// �Q�ڂ̏Փ˔���O���[�v�͈̔͂�\���C�e���[�^�y�A
			auto secondGroup = m_collisionList.equal_range(collisionGroupPair.second);

			// �P�ڂ̏Փ˔���O���[�v�����񂷂�
			for (auto firstItr = firstGroup.first; firstItr != firstGroup.second; firstItr++)
			{
				// �Q�ڂ̏Փ˔���O���[�v�����񂷂�
				for (auto secondItr = secondGroup.first; secondItr != secondGroup.second; secondItr++)
				{
					// �P�ڂ̃O���[�v�̗v�f�̏Փ˔���֐����Q�ڂ̃O���[�v�̗v�f�������Ɏ��s����
					(*firstItr).second.runCollideFunc((*secondItr).second);
				}
			}
		}
	}

	void ComponentCollisionList::movePreFrameAddedNode()
	{
		// ���C�����X�g�Ɉړ�����v�f�����������X�g������
		for (const auto& node : m_nextFrameAddNodeList)
		{
			// ���C�����X�g�ɗv�f���R�s�[
			m_collisionList.insert(node);
		}

		// �R�s�[���̃R���e�i�͍폜
		m_nextFrameAddNodeList.clear();
	}

	void ComponentCollisionList::removeDeadComponent()
	{
		// ���C�����X�g�����񂷂�
		for (auto itr = std::begin(m_collisionList); itr != std::end(m_collisionList);)
		{
			// �����Ώۂ̗v�f�̎��S�t���O�������Ă�����
			if ((*itr).second.isDead())
			{
				// ���̗v�f���폜���C�e���[�^�̒l�����Ƀ`�F�b�N����ΏۂɕύX����
				itr = m_collisionList.erase(itr);
				continue;
			}
			// �C�e���[�^���C���N�������g
			++itr;
		}
	}

	void ComponentCollisionList::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		// �V���ȏՓ˔���O���[�v��ǉ�����
		m_collisionGroupPairArray.push_back(std::make_pair(firstGroup, secondGroup));
	}

	void ComponentCollisionList::add(const ComponentBasePtr& componentPtr, ComponentCollisionFuncVTable* vtablePtr)
	{
		m_nextFrameAddNodeList.emplace_front(std::make_pair(
			componentPtr->getCollisionGroup(),
			ComponentCollisionFuncRunner(componentPtr, vtablePtr)
		));
	}
	
}