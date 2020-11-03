#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineList.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachine.h"

namespace tktk
{
	StateMachineList::StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList)
	{
		// �e�̏�Ԃ������Ȃ��X�e�[�g�}�V�������
		for (const auto& node : initParam.m_roots)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(user, node.m_id);

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			m_stateMachineList[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// �e�̏�Ԃ����X�e�[�g�}�V������邽�߂ɍċN�������s��
			createNode(m_stateMachineList.at(node.m_id), node, user, componentList);
		}
	}

	void StateMachineList::addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child)
	{
		(*getTarget(targetState)).m_stateMachine->addChild(child);
	}

	void StateMachineList::addComponent(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr)
	{
		(*getTarget(targetState)).m_stateMachine->addComponent(componentPtr);
	}

	StateTypeList StateMachineList::getChildNode(const StateTypeHierarchy& targetState) const
	{
		// ���ʂ�Ԃ����߂̃R���e�i�i�d�����Ȃ��悤��set���g���j
		auto result = StateTypeList();

		// �����̃X�e�[�g���擾���A�ċA�֐����Ă�
		getChildNodeImpl(&result, getTarget(targetState));

		return result;
	}

	void StateMachineList::createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList)
	{
		// �e�̏�Ԃ����X�e�[�g�}�V�������
		for (const auto& node : nodeInitParam.m_children)
		{
			// �X�e�[�g�}�V���������
			auto createdComponent = DX12GameManager::createComponent<StateMachine>(user, node.m_id);

			// �e�̃X�e�[�g�}�V���ɓo�^��
			parentNode.m_stateMachine->addComponent(ComponentBasePtr(createdComponent));

			// �X�e�[�g�}�V�����X�g�ɓo�^����
			parentNode.m_childNode[node.m_id] = { componentList->add<StateMachine>(createdComponent), {} };

			// ����Ȃ�q�v�f����邽�߂ɍċN����
			createNode(parentNode.m_childNode.at(node.m_id), node, user, componentList);
		}
	}

	const StateMachineList::Node* StateMachineList::getTarget(const StateTypeHierarchy& targetState) const
	{
#ifdef _DEBUG
		if (targetState.hierarchy.size() == 0)  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG

		// ���݂̊K�w��\���|�C���^
		const StateMachineList::Node* curNodePtr = nullptr;

		// �Ώۂ̃X�e�[�g�̊K�w�����[�v����
		for (const auto& node : targetState.hierarchy)
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

		// ���݂̊K�w���s���ł͂Ȃ���΂��̒l��Ԃ�
		if (curNodePtr != nullptr) return curNodePtr;

#ifdef _DEBUG
		else  throw std::runtime_error("targetState fraud value");
#endif // _DEBUG
		return nullptr;
	}

	void StateMachineList::getChildNodeImpl(StateTypeList* result, const StateMachineList::Node* target) const
	{
		// �q�X�e�[�g�����񂷂�
		for (const auto& node : target->m_childNode)
		{
			result->list.insert(node.first);

			// ����Ȃ鑷�X�e�[�g�����񂷂邽�߂̍ċA����
			getChildNodeImpl(result, &node.second);
		}
	}
}