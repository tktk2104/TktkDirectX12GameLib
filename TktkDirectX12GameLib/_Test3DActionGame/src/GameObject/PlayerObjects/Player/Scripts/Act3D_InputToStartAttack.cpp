#include "Act3D_InputToStartAttack.h"

#include "../../../../Enums/Enums.h"

void Act3D_InputToStartAttack::update()
{
	if (tktk::DX12Game::isTrigger(tktk::KeybordKeyType::key_Space))
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
		getGameObject()->stateDisable(PlayerStateType::Move);
		getGameObject()->stateDisable(PlayerStateType::Idle);
		getGameObject()->stateDisable(PlayerStateType::WalkForward);
		getGameObject()->stateDisable(PlayerStateType::WalkBackward);
		getGameObject()->stateDisable(PlayerStateType::WalkLeft);
		getGameObject()->stateDisable(PlayerStateType::WalkRight);
		getGameObject()->stateDisable(PlayerStateType::RunForward);
	}
}
