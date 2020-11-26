#include "Act3D_InputToStartComboAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartComboAttack::onEnable()
{
	m_invalidStateChangeSecTimer = 0.0f;
	m_afterInput = false;
}

void Act3D_InputToStartComboAttack::update()
{
	// �U���{�^���������ꂽ��
	if (tktk::DX12Game::isTrigger(CommandId::Attack))
	{
		m_afterInput = true;
	}

	if (m_invalidStateChangeSecTimer < InvalidStateChangeTimeSec)
	{
		m_invalidStateChangeSecTimer += tktk::DX12Game::deltaTime();
		return;
	}

	if (m_afterInput)
	{
		// �U���i��i�j��Ԃ�؂�
		getGameObject()->stateDisable(PlayerStateType::Attack1);

		// �U���i��i�j��Ԃɂ���
		getGameObject()->stateEnable(PlayerStateType::Attack2);
	}
}
