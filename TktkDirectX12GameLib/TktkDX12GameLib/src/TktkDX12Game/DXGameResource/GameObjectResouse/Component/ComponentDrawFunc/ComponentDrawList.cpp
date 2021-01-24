#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentDrawFunc/ComponentDrawList.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentDrawFunc/ComponentDrawFuncRunner.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentVTable.h"

namespace tktk
{
	// �R���X�g���N�^���C�����C��������
	ComponentDrawList::ComponentDrawList() = default;

	// �f�X�g���N�^���C�����C��������
	ComponentDrawList::~ComponentDrawList() = default;

	void ComponentDrawList::add(const ComponentBasePtr& componentPtr, ComponentDrawFuncVTable* vtablePtr)
	{
		if (vtablePtr->hasDrawFunc())
		{
			m_nextFrameAddNodeList.emplace_front(componentPtr->getDrawPriority(), ComponentDrawFuncRunner(componentPtr, vtablePtr));
		}
	}

	void ComponentDrawList::runDrawFunc() const
	{
		// �`��֐��Ăяo���N���X�����񂷂�
		for (const auto& drawFuncRunner : m_drawList)
		{
			// �`��֐����Ă�
			drawFuncRunner.second.runDrawFunc();
		}
	}

	void ComponentDrawList::movePreFrameAddedNode()
	{
		// ���C�����X�g�Ɉړ�����v�f�����������X�g������
		for (const auto& node : m_nextFrameAddNodeList)
		{
			// ���C�����X�g�ɗv�f���R�s�[
			m_drawList.insert(node);
		}

		// �R�s�[���̃R���e�i�͍폜
		m_nextFrameAddNodeList.clear();
	}

	void ComponentDrawList::removeDeadComponent()
	{
		// ���C�����X�g�����񂷂�
		for (auto itr = std::begin(m_drawList); itr != std::end(m_drawList);)
		{
			// �����Ώۂ̗v�f�̎��S�t���O�������Ă�����
			if ((*itr).second.isDead())
			{
				// ���̗v�f���폜���C�e���[�^�̒l�����Ƀ`�F�b�N����ΏۂɕύX����
				itr = m_drawList.erase(itr);
				continue;
			}
			// �C�e���[�^���C���N�������g
			++itr;
		}
	}
}