#include "Act3D_InputToStartComboAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartComboAttack::onEnable()
{
	// �����o�ϐ���������
	m_invalidStateChangeSecTimer = 0.0f;
	m_afterInput = false;
}

void Act3D_InputToStartComboAttack::update()
{
	// �U���{�^���������ꂽ��
	if (tktk::DX12Game::isTrigger(CommandId::Attack))
	{
		// ���͌�t���O�𗧂Ă�
		m_afterInput = true;
	}

	// �^�C�}�[������̒l�ɒB���Ă��Ȃ����
	if (m_invalidStateChangeSecTimer < InvalidStateChangeTimeSec)
	{
		// �^�C�}�[���J�E���g�A�b�v
		m_invalidStateChangeSecTimer += tktk::DX12Game::deltaTime();
		return;
	}

	// ���ɍU���{�^����������Ă�����
	if (m_afterInput)
	{
		// �U���i��i�j��Ԃ�؂�
		getGameObject()->stateDisable(PlayerStateType::Attack1);

		// �U���i��i�j��Ԃɂ���
		getGameObject()->stateEnable(PlayerStateType::Attack2);
	}
}
