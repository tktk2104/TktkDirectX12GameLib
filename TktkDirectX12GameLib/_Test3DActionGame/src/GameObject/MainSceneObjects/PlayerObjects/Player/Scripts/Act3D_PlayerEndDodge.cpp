#include "Act3D_PlayerEndDodge.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerEndDodge::start()
{
	m_meshDrawer = getComponent<tktk::MeshDrawer>();

	if (m_meshDrawer.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found MeshDrawer");
	}
}

void Act3D_PlayerEndDodge::onEnable()
{
	// �^�C�}�[��������
	m_endDodgeSecTimer = EndDodgeTimeSec;
}

void Act3D_PlayerEndDodge::update()
{
	if (m_endDodgeSecTimer < 0.0f)
	{
		// �ʏ�E�ړ���Ԃ�L���ɂ���
		getGameObject()->statesEnable({ PlayerStateType::Normal, PlayerStateType::Move });

		// �����Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(PlayerStateType::Dodge);

		// ���b�V���̃��[�J����]�����ɖ߂�
		m_meshDrawer->setBaseRotation(tktkMath::Quaternion::createFromEulerAngle({0.0f, 180.0f, 0.0f}));
		return;
	}

	// �^�C�}�[���X�V����
	m_endDodgeSecTimer -= tktk::DX12Game::deltaTime();
}
