#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentMainList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentMainList/ComponentTypeList.h"

namespace tktk
{
	// �R���X�g���N�^���C�����C��������
	ComponentMainList::ComponentMainList() = default;

	// �f�X�g���N�^���C�����C��������
	ComponentMainList::~ComponentMainList() = default;

	void ComponentMainList::addComponent(std::type_index type, ComponentListVTable* vtablePtr, const std::shared_ptr<ComponentBase>& componentPtr)
	{
		// �e���v���[�g�����̃R���|�[�l���g���ȑO�ɒǉ����ꂽ�������邩���ׂ�
		auto findNode = m_addComponentMap.find(type);

		// �����A���񂪏��߂Ēǉ�������ނ̃R���|�[�l���g�������ꍇ�A
		if (findNode == std::end(m_addComponentMap))
		{
			auto createList = std::make_shared<ComponentTypeList>(vtablePtr);
			m_mainMap.emplace(m_priorityList.getPriority(type), createList);
			m_addComponentMap.emplace(type, createList);

			// �ǉ��������X�g���擾����
			findNode = m_addComponentMap.find(type);
		}

		findNode->second.lock()->addComponent(componentPtr);
	}

	void ComponentMainList::addRunFuncPriority(std::type_index type, float priority)
	{
		m_priorityList.addPriority(type, priority);
	}

	void ComponentMainList::movePreFrameAddedNode()
	{
		// �O�t���[���ɒǉ������v�f��{���X�g�ɒǉ�����
		for (const auto& node : m_mainMap)
		{
			node.second->moveNewComponent();
		}
	}

	void ComponentMainList::activeChangeCheck()
	{
		// �A�N�e�B�u�t���O�̔���ƃt���O�ύX���̊֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}
	}

	void ComponentMainList::update()
	{
		// �uupdate�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}
	}

	void ComponentMainList::runBeforeCollide()
	{
		// �urunAfterCollide�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->runBeforeCollide();
		}
	}

	void ComponentMainList::runAfterCollide()
	{
		// �urunAfterCollide�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->runAfterCollide();
		}
	}

	void ComponentMainList::removeDeadComponent()
	{
		// �urunAfterCollide�v�֐��Ăяo������
		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}
	}
}