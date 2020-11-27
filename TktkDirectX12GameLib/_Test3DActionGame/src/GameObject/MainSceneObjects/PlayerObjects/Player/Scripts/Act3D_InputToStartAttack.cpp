#include "Act3D_InputToStartAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartAttack::update()
{
	// �U���Ԋu�^�C�}�[�̃J�E���g���[���ɂȂ��ĂȂ����
	if (m_attackIntervelSecTimer > 0.0f)
	{
		// �^�C�}�[���J�E���g�_�E�����A�������I����
		m_attackIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// �U���{�^���������ꂽ��
	if (tktk::DX12Game::isTrigger(CommandId::Attack))
	{
		// �U����Ԃɂ���
		getGameObject()->stateEnable(PlayerStateType::Attack);

		// ���g�������Ԃ�������
		if (getGameObject()->containState(PlayerStateType::RunForward))
		{
			// �W�����v�A�^�b�N��Ԃɂ���
			getGameObject()->stateEnable(PlayerStateType::JumpAttack);
		}
		else
		{
			// �U���i��i�j��Ԃɂ���
			getGameObject()->stateEnable(PlayerStateType::Attack1);
		}

		// �ړ��Ɋ֌W����X�e�[�g����U�S�Đ؂�
		getGameObject()->statesDisable({
			PlayerStateType::Move,
			PlayerStateType::Idle,
			PlayerStateType::WalkForward,
			PlayerStateType::WalkBackward,
			PlayerStateType::WalkLeft,
			PlayerStateType::WalkRight,
			PlayerStateType::RunForward
			});

		// �U���̃C���^�[�o���^�C�}�[�����Z�b�g����
		m_attackIntervelSecTimer = AttackIntervalTimeSec;
	}
}
