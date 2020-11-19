#include "Act3D_InputToStartAttack.h"

#include "../../../../Enums/Enums.h"

void Act3D_InputToStartAttack::update()
{
	if (tktk::DX12Game::isTrigger(tktk::KeybordKeyType::key_Space))
	{
		// 攻撃状態にする
		getGameObject()->stateEnable(PlayerStateType::Attack);

		// 自身が走り状態だったら
		if (getGameObject()->containState(PlayerStateType::RunForward))
		{
			// ジャンプアタック状態にする
			getGameObject()->stateEnable(PlayerStateType::JumpAttack);
		}
		else
		{
			// 攻撃（一段）状態にする
			getGameObject()->stateEnable(PlayerStateType::Attack1);
		}

		// 移動に関係するステートを一旦全て切る
		getGameObject()->stateDisable(PlayerStateType::Move);
		getGameObject()->stateDisable(PlayerStateType::Idle);
		getGameObject()->stateDisable(PlayerStateType::WalkForward);
		getGameObject()->stateDisable(PlayerStateType::WalkBackward);
		getGameObject()->stateDisable(PlayerStateType::WalkLeft);
		getGameObject()->stateDisable(PlayerStateType::WalkRight);
		getGameObject()->stateDisable(PlayerStateType::RunForward);
	}
}
