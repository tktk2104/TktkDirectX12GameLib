#include"TktkDX12BaseComponents/3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ColliderWireFrameDrawer3DMaker ColliderWireFrameDrawer3DMaker::m_self;

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = ColliderWireFrameDrawer3DMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer3D> ColliderWireFrameDrawer3DMaker::create()
	{
		// �R���|�[�l���g���쐬����
		return m_user->createComponent<ColliderWireFrameDrawer3D>(m_lineColor);
	}

	ColliderWireFrameDrawer3DMaker& ColliderWireFrameDrawer3DMaker::lineColor(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_lineColor = value;
		return *this;
	}
}