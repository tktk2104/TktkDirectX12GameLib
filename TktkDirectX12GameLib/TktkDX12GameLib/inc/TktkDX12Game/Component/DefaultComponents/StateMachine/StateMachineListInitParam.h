#ifndef STATE_MACHINE_LIST_INIT_PARAM_H_
#define STATE_MACHINE_LIST_INIT_PARAM_H_

#include <vector>

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

			Node(int id);
			Node(int id, const std::vector<Node>& child);

		public:

			int					m_id;
			std::vector<Node>	m_child;
		};

	public:

		StateMachineListInitParam(const std::vector<Node>& roots);

	public:

		// ��ԏ�̊K�w�̗v�f
		std::vector<Node>	m_roots;
	};
}
#endif // !STATE_MACHINE_LIST_INIT_PARAM_H_