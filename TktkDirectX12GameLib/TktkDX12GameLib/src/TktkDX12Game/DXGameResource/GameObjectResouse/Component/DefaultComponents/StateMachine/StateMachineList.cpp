#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/StateMachineList.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/StateMachine.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/Structs/StateTypeList.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/DefaultComponents/StateMachine/Structs/StateTypeHierarchy.h"

namespace tktk
{
	StateMachineList::StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user)
	{
		// �e�̏�Ԃ������Ȃ��X�e�[�g�}�V�������
		for (const auto& node : initParam.m_roots)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = user->createComponent<StateMachine>(node.m_id);

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			m_stateMachineList[node.m_id] = { createdComponent, {} };

			// �e�̏�Ԃ����X�e�[�g�}�V������邽�߂ɍċN�������s��
			createNode(m_stateMachineList.at(node.m_id), node, user);
		}
	}

	void StateMachineList::setTargetHierarchy(const StateTypeHierarchy& targetHierarchy)
	{
		m_targetHierarchy = targetHierarchy;
	}

	bool StateMachineList::isSetTargetHierarchy() const
	{
		return !getTargetStateMachine().expired();
	}

	void StateMachineList::addChild(const GameObjectPtr& child)
	{
		auto targetStateMachine = getTargetStateMachine();

		if (targetStateMachine.expired()) return;

		targetStateMachine->addChild(child);
	}

	void StateMachineList::removeChild(const GameObjectPtr& child)
	{
		// �S�Ă̊K�w��������̃I�u�W�F�N�g���폜���邽�߂ɍċA����
		removeChildImpl(m_stateMachineList, child);
	}

	void StateMachineList::addComponent(const ComponentBasePtr& componentPtr)
	{
		auto targetStateMachine = getTargetStateMachine();

		if (targetStateMachine.expired()) return;

		targetStateMachine->addComponent(componentPtr);
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user)
	{
		// �e�̏�Ԃ����X�e�[�g�}�V�������
		for (const auto& node : nodeInitParam.m_children)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = user->createComponent<StateMachine>(node.m_id);

			// �e�̃X�e�[�g�}�V���ɓo�^��
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			parentNode.m_childNode[node.m_id] = { createdComponent, {} };

			// ����Ȃ�q�v�f����邽�߂ɍċN����
			createNode(parentNode.m_childNode.at(node.m_id), node, user);
		}
	}

	ComponentPtr<StateMachine> StateMachineList::getTargetStateMachine() const
	{
		// ���݂̊K�w��\���|�C���^
		const StateMachineList::Node* curNodePtr = nullptr;

		// �Ώۂ̃X�e�[�g�̊K�w�����[�v����
		for (const auto& node : m_targetHierarchy.hierarchy)
		{
			// �����񃋁[�v���̂݃A���S���Y�����Ⴄ
			if (curNodePtr == nullptr)
			{
#ifdef _DEBUG
				if (m_stateMachineList.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

				// ��ԏ�̊K�w���擾����
				curNodePtr = &m_stateMachineList.at(node);

				// ���̗v�f�ֈڍs����
				continue;
			}

#ifdef _DEBUG
			if (curNodePtr->m_childNode.count(node) == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

			// ���̗v�f�̊K�w���擾����
			curNodePtr = &curNodePtr->m_childNode.at(node);
		}

		// �u���݂̊K�w��\���|�C���^�v�� nullptr �łȂ���ΑΏۂ̃X�e�[�g�}�V�����Anullptr ���������̃R���|�[�l���g�|�C���^��Ԃ�
		return (curNodePtr != nullptr) ? curNodePtr->m_stateMachine : ComponentPtr<StateMachine>();
	}

	void StateMachineList::removeChildImpl(const std::unordered_map<StateTypeCarrier, Node>& targetMap, const GameObjectPtr& child)
	{
		for (const auto& pair : targetMap)
		{
			pair.second.m_stateMachine->removeChild(child);

			// �ċA����
			removeChildImpl(pair.second.m_childNode, child);
		}
	}
}