#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentManager.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentMainList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentStartFunc/ComponentStartList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentDrawFunc/ComponentDrawList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/ComponentCollisionList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"

namespace tktk
{
	// �R���X�g���N�^���C�����C��������
	ComponentManager::ComponentManager()
	{
		m_componentMainList			= std::make_unique<ComponentMainList>();
		m_componentStartList		= std::make_unique<ComponentStartList>();
		m_componentDrawList			= std::make_unique<ComponentDrawList>();
		m_componentCollisionList	= std::make_unique<ComponentCollisionList>();
	}

	// �f�X�g���N�^���C�����C��������
	ComponentManager::~ComponentManager() = default;

	void ComponentManager::movePreFrameAddedNode()
	{
		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		m_componentMainList->movePreFrameAddedNode();
		m_componentStartList->movePreFrameAddedNode();
		m_componentDrawList->movePreFrameAddedNode();
		m_componentCollisionList->movePreFrameAddedNode();
	}

	void ComponentManager::update()
	{
		// �A�N�e�B�u��Ԃ̔�����s��
		m_componentMainList->activeChangeCheck();

		// �ustart�v�֐��Ăяo������
		m_componentStartList->runStartFunc();
		
		// �X�V�������Ă�
		m_componentMainList->update();

		// �Փ˔��蒼�O�������Ă�
		m_componentMainList->runBeforeCollide();

		// �Փ˔���n�֐��Ăяo������
		m_componentCollisionList->runCollisionFunc();

		// �Փ˔���㏈�����Ă�
		m_componentMainList->runAfterCollide();
	}

	void ComponentManager::removeDeadComponent()
	{
		// ���񂾃R���|�[�l���g���폜����
		m_componentMainList->removeDeadComponent();

		// �Փ˔��胊�X�g���Ǘ����Ă���R���|�[�l���g�|�C���^�̐����m�F
		m_componentCollisionList->removeDeadComponent();

		// �`�惊�X�g���Ǘ����Ă���R���|�[�l���g�|�C���^�̐����m�F
		m_componentDrawList->removeDeadComponent();

		// ���Ɂustart�v�֐����Ă΂ꂽ���A���S�t���O�������Ă���R���|�[�l���g���폜����
		m_componentStartList->removeDeadComponent();
	}

	void ComponentManager::draw()
	{
		// �udraw()�v�֐��Ăяo������
		m_componentDrawList->runDrawFunc();
	}

	void ComponentManager::addRunFuncPriority(std::type_index type, float priority)
	{
		m_componentMainList->addRunFuncPriority(type, priority);
	}

	void ComponentManager::addCollisionGroup(CollisionGroupTypeCarrier firstGroup, CollisionGroupTypeCarrier secondGroup)
	{
		// �Փ˔���̑g�ݍ��킹��ǉ�
		m_componentCollisionList->addCollisionGroup(firstGroup, secondGroup);
	}

	ComponentBasePtr ComponentManager::addComponent(std::type_index type, ComponentVTableBundle* vtablePtrBundle, ComponentListVTable* listVtablePtr, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		m_componentMainList->addComponent(type, listVtablePtr, componentPtr);

		ComponentBasePtr createdPtr = ComponentBasePtr(type, componentPtr);

		// �e��֐��Ăяo���������X�g�ɂ���weak_ptr��n��
		m_componentStartList->add(createdPtr, vtablePtrBundle->startFuncVTable);
		m_componentCollisionList->add(createdPtr, vtablePtrBundle->collisionFuncVTable);
		m_componentDrawList->add(createdPtr, vtablePtrBundle->drawFuncVTable);

		// ������R���|�[�l���g��weak_ptr��Ԃ��ďI��
		return createdPtr;
	}
}