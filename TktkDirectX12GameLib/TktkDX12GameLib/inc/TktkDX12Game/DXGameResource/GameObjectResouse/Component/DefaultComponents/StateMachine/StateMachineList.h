#ifndef STATE_MACHINE_LIST_H_
#define STATE_MACHINE_LIST_H_

/* std::unordered_map */
#include <unordered_map>

/* selfInitParam */
#include "Structs/StateMachineListInitParam.h"

/* funcUseType */
#include "Structs/StateTypeList.h"

/* class member */
#include "../../ComponentPtr.h"
#include "Structs/StateTypeHierarchy.h"

namespace tktk
{
	/* funcUseType */
	class ComponentBasePtr;
	class GameObjectPtr;

	/* class member */
	class StateMachine;

	// �X�e�[�g�}�V���̃|�C���^���Ǘ�����N���X
	// ��GameObject�́usetupStateMachine�v�֐��ō쐬�����
	class StateMachineList
	{
	public:

		StateMachineList(const StateMachineListInitParam& initParam, const GameObjectPtr& user);

	public:

		// �q�v�f�A�R���|�[�l���g��ǉ�����X�e�[�g�̊K�w��ݒ肷��
		// �����ケ�̊֐����ĂьĂ΂��܂Œǉ�����X�e�[�g�̊K�w���Œ肳���
		void setTargetHierarchy(const StateTypeHierarchy& targetHierarchy);

		// �R���|�[�l���g��ǉ�����K�w���o�^����Ă��邩���肷��
		bool isSetTargetHierarchy() const;

		// ���O�ɐݒ肵���K�w�Ɏq�v�f��ǉ�����
		void addChild(const GameObjectPtr& child);

		// �S�Ă̊K�w����q�v�f���폜����
		void removeChild(const GameObjectPtr& child);

		// ���O�ɐݒ肵���K�w�ɃR���|�[�l���g��ǉ�����
		void addComponent(const ComponentBasePtr& componentPtr);

	private:

		// ����q�P���̗v�f
		struct Node
		{
			ComponentPtr<StateMachine>					m_stateMachine;
			std::unordered_map<StateTypeCarrier, Node>	m_childNode;
		};

	private:

		// �e�̏�Ԃ����X�e�[�g�}�V�������
		void createNode(StateMachineList::Node& parentNode, const StateMachineListInitParam::Node& nodeInitParam, const GameObjectPtr& user);

		// �q�v�f�A�R���|�[�l���g��ǉ�����X�e�[�g�̊K�w�����擾����
		ComponentPtr<StateMachine> getTargetStateMachine() const;

		void removeChildImpl(const std::unordered_map<StateTypeCarrier, Node>& targetMap, const GameObjectPtr& child);

	private:

		// �q�v�f�A�R���|�[�l���g��ǉ�����X�e�[�g�̊K�w
		StateTypeHierarchy							m_targetHierarchy	{};

		// ����q�\���ŃX�e�[�g�}�V�����Ǘ�����
		std::unordered_map<StateTypeCarrier, Node>	m_stateMachineList	{};
	};
}
#endif // !STATE_MACHINE_LIST_H_