#include "TktkDX12Game/Component/DefaultComponents/StateMachine/StateMachineListInitParam.h"

namespace tktk
{
	void StateMachineListInitParam::initRootNode(StateTypeList roots)
	{
		// ��ԏ�̊K�w�̗v�f�̔z��̃������m�ۂ��s��
		m_roots.reserve(roots.list.size());

		// �ϐ��̏��������s��
		for (const auto& root : roots.list)
		{
			m_roots.push_back(root);
		}
	}

	void StateMachineListInitParam::addChildNode(StateTypeHierarchy hierarchy, StateTypeList child)
	{
		// ���݂̃X�e�[�g��\���|�C���^
		Node* curNodePtr = nullptr;

		// �X�e�[�g�̊K�w�����[�v����
		for (const auto& node : hierarchy.hierarchy)
		{
			// ���񃋁[�v�̂݃A���S���Y�����Ⴄ
			if (curNodePtr == nullptr)
			{
				// ��ԏ�̊K�w�̗v�f�����񂷂�
				for (auto& rootsNode : m_roots)
				{
					// �X�e�[�g�̊K�w�̓������������擾���A�Ή�����m�[�h��T��
					if (rootsNode.m_id == (*hierarchy.hierarchy.begin())) curNodePtr = &rootsNode;
				}

				// �Ή������ԏ�̊K�w���擾�ł��Ȃ���΂����ŏ������I����
				if (curNodePtr == nullptr) return;

				// ���̗v�f��
				continue;
			}

			// �Ή�����K�w���擾�ł������H
			bool findChild = false;

			// ���݂̃X�e�[�g�̎q�v�f�����[�v����
			for (auto& child : curNodePtr->m_children)
			{
				// �q�v�f�̃X�e�[�g�Ǝ��ɐi�ނׂ��K�w�̃X�e�[�g����v������
				if (child.m_id == node)
				{
					// �Ή�����K�w���擾�����t���O�𗧂Ă�
					findChild = true;

					// ���݂̃X�e�[�g���X�V����
					curNodePtr = &child;

					// ���̃��[�v���I����
					break;
				}
			}

			// �Ή�����K�w���擾�ł��Ȃ���΂����ŏ������I����
			if (!findChild) return;
		}

		// �Ώۂ̊K�w�̎q�v�f�̃R���e�i�̃��������m�ۂ���
		curNodePtr->m_children.reserve(child.list.size());

		// �Ώۂ̊K�w�̎q�v�f�̃R���e�i�ɗv�f��ǉ�����
		for (const auto& type : child.list) curNodePtr->m_children.push_back(type);
	}
}