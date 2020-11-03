#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ColliderWireFrameDrawer2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ColliderWireFrameDrawer2DMaker& ColliderWireFrameDrawer2DMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ColliderWireFrameDrawer2DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �����̒ǉ��K�w��ݒ�
		m_self.m_targetState = targetState;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		// ���g��ǉ�����K�w��񂪋󂾂����畁�ʂɍ쐬����
		if (m_targetState.hierarchy.empty())
		{
			// �R���|�[�l���g���쐬���Ă��̃|�C���^��Ԃ�
			return m_user->createComponent<ColliderWireFrameDrawer2D>(
				m_drawPriority,
				m_lineColor
				);
		}

		// �R���|�[�l���g���쐬����
		auto createComponent = m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_lineColor
			);

		// �쐬�����R���|�[�l���g�����̃X�e�[�g�ɒǉ�����
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// �쐬�����R���|�[�l���g�̃|�C���^��Ԃ�
		return createComponent;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::drawPriority(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::lineColor(const tktkMath::Color & value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineColor = value;
		return *this;
	}
}