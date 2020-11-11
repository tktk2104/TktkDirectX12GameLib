#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentStartFunc/ComponentStartList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentStartFunc/ComponentStartFuncRunner.h"

namespace tktk
{
	// �R���X�g���N�^���C�����C��������
	ComponentStartList::ComponentStartList() = default;

	// �f�X�g���N�^���C�����C��������
	ComponentStartList::~ComponentStartList() = default;

	void ComponentStartList::add(const ComponentBasePtr& componentPtr, ComponentStartFuncVTable* vtablePtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr, vtablePtr);
	}

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