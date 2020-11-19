#include "Act3D_PlayerController.h"

#include "../../../../Enums/Enums.h"

Act3D_PlayerController::Act3D_PlayerController(float moveSpeedPerSec, float rotateDegSpeedPerSec)
	: m_moveSpeedPerSec(moveSpeedPerSec)
	, m_rotateDegSpeedPerSec(rotateDegSpeedPerSec)
{
}

void Act3D_PlayerController::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_InputToMove not found Transform3D");
	}
}

void Act3D_PlayerController::update()
{
	// ˆÚ“®‚ÉŠÖŒW‚·‚éƒXƒe[ƒg‚ðˆê’U‘S‚ÄØ‚é
	getGameObject()->stateDisable(PlayerStateType::Idle);
	getGameObject()->stateDisable(PlayerStateType::WalkForward);
	getGameObject()->stateDisable(PlayerStateType::WalkBackward);
	getGameObject()->stateDisable(PlayerStateType::WalkLeft);
	getGameObject()->stateDisable(PlayerStateType::WalkRight);
	getGameObject()->stateDisable(PlayerStateType::RunForward);

	// ˆÚ“®•ûŒü‚ðŽæ“¾‚·‚é
	auto moveDir = tktkMath::Vector3_v::zero;

	auto moveSpeed = m_moveSpeedPerSec;

	auto playerMoveState = PlayerStateType::Idle;

	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_A))
	{
		moveDir -= m_transform->calculateWorldRight();

		playerMoveState = PlayerStateType::WalkLeft;
	}
	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_D))
	{
		moveDir += m_transform->calculateWorldRight();

		playerMoveState = PlayerStateType::WalkRight;
	}
	
	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_W))
	{
		moveDir += m_transform->calculateWorldForwardLH();

		if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_Lshift) || tktk::DX12Game::isPush(tktk::KeybordKeyType::key_Rshift))
		{
			playerMoveState = PlayerStateType::RunForward;
			moveSpeed *= 2.0f;
		}
		else
		{
			playerMoveState = PlayerStateType::WalkForward;
		}
	}
	else if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_S))
	{
		moveDir -= m_transform->calculateWorldForwardLH();

		playerMoveState = PlayerStateType::WalkBackward;
	}

	m_transform->addLocalPosition(moveDir.normalized() * moveSpeed * tktk::DX12Game::deltaTime());


	getGameObject()->stateEnable(playerMoveState);

	// “ü—Í‚É‰ž‚¶‚ÄŽ©g‚ð‰ñ“]‚³‚¹‚é
	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_Left))
	{
		m_transform->addLocalEulerAngles({ 0.0f,  -m_rotateDegSpeedPerSec * tktk::DX12Game::deltaTime(), 0.0f });
	}
	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_Right))
	{
		m_transform->addLocalEulerAngles({ 0.0f, m_rotateDegSpeedPerSec * tktk::DX12Game::deltaTime(), 0.0f });
	}
}
