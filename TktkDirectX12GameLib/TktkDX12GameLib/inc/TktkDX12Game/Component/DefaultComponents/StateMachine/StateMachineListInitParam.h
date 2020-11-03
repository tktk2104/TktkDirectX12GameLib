#ifndef STATE_MACHINE_LIST_INIT_PARAM_H_
#define STATE_MACHINE_LIST_INIT_PARAM_H_

#include <vector>
#include "StateTypeList.h"
#include "StateTypeHierarchy.h"

namespace tktk
{
	// �X�e�[�g�}�V������邽�߂ɕK�v�ȕϐ�
	struct StateMachineListInitParam
	{
	public:

		// �X�e�[�g�̗v�f�i����q�\���ɂȂ��Ă���j
		struct Node
		{
		public:

			Node(StateTypeCarrier id) 
				: m_id(id) , m_children() {};
			Node(StateTypeCarrier id, const std::vector<Node>& children) 
				: m_id(id) , m_children(children) {};

		public:

			StateTypeCarrier	m_id;
			std::vector<Node>	m_children;
		};

	public:

		// �f�t�H���g�R���X�g���N�^
		StateMachineListInitParam() = default;

	public:

		// ��ԏ�̊K�w�̃X�e�[�g��ݒ肷��
		void initRootNode(StateTypeList roots);

		// �w��̊K�w�̃X�e�[�g�Ɏq�X�e�[�g��ǉ�����
		void addChildNode(StateTypeHierarchy hierarchy, StateTypeList child);

	public:

		// ��ԏ�̊K�w�̗v�f
		std::vector<Node>	m_roots;
	};
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_