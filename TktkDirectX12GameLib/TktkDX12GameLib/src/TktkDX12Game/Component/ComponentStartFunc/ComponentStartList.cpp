#include "TktkDX12Game/Component/ComponentStartFunc/ComponentStartList.h"

namespace tktk
{
	void ComponentStartList::runStartFunc()
	{
		// �J�n���֐��Ăяo���N���X�����񂷂�
		// �����X�g�̗v�f��ύX����̂Ŕ�const
		for (auto& startFuncRunner : m_startList)
		{
			// �J�n���֐����Ă�
			startFuncRunner.runStart();
		}
	}

	void ComponentStartList::movePreFrameAddedNode()
	{
		// ���C�����X�g�Ɉړ������񂪓��������X�g�̗v�f�����C�����X�g�Ɉړ�
		for (const auto& node : m_nextFrameAddNodeList)
		{
			m_startList.push_front(node);
		}

		// �R�s�[���̃R���e�i�͍폜
		m_nextFrameAddNodeList.clear();
	}

	void ComponentStartList::removeDeadComponent()
	{
		// ���S�t���O�̗������R���|�[�l���g�����X�g����폜����
		m_startList.remove_if([](const auto& node) { return node.isDead(); });
	}
}