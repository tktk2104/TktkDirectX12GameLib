#ifndef STATE_MACHINE_LIST_H_
#define STATE_MACHINE_LIST_H_

#include <memory>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "../../../GameObject/GameObjectPtr.h"
#include "../../ComponentBasePtr.h"
#include "StateMachineListInitParam.h"

namespace tktk
{
	class GameObjectComponentList;
	class StateMachine;

	// �X�e�[�g�}�V���̃|�C���^���Ǘ�����N���X
	// ��GameObject�́usetupStateMachine�v�֐��ō쐬�����
	class StateMachineList
	{
	public:

		StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList);

	public:

		// �X�e�[�g���K�w�Ŏw�肵�A�q�v�f��ǉ�����
		// ���u{ 1, 10, 30 }�v�Łu�g�X�e�[�g�P�h���́g�X�e�[�g�P�O�h���́g�X�e�[�g�R�O�h�ɒǉ��v�ƂȂ�
		void addChild(const StateTypeHierarchy& targetState, const GameObjectPtr& child);

		// �X�e�[�g���K�w�Ŏw�肵�A�����̃R���|�[�l���g��ǉ�����
		// ���u{ 1, 10, 30 }�v�Łu�g�X�e�[�g�P�h���́g�X�e�[�g�P�O�h���́g�X�e�[�g�R�O�h�ɒǉ��v�ƂȂ�
		void addComponent(const StateTypeHierarchy& targetState, const ComponentBasePtr& componentPtr);

		// �X�e�[�g���K�w�Ŏw�肵���̃X�e�[�g�̎q�X�e�[�g�̎�ނ�S�Ď擾����
		StateTypeList getChildNode(const StateTypeHierarchy& targetState) const;

	private:

		// ����q�P���̗v�f
		struct Node
		{
			ComponentPtr<StateMachine>					m_stateMachine;
			std::unordered_map<StateTypeCarrier, Node>	m_childNode;
		};

	private:

		// �e�̏�Ԃ����X�e�[�g�}�V�������
		void createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user, const std::unique_ptr<GameObjectComponentList>& componentList);

		// int�^�̔z�񂩂�w��̃X�e�[�g���擾����
		const StateMachineList::Node* getTarget(const StateTypeHierarchy& targetState) const;

		// �ugetChildNode()�v�̍ċA�p�֐�
		void getChildNodeImpl(StateTypeList* result, const StateMachineList::Node* target) const;

	private:

		// ����q�\���Ń|�C���^���Ǘ�����
		std::unordered_map<StateTypeCarrier, Node>	m_stateMachineList;
	};
}
#endif // !STATE_MACHINE_LIST_H_
