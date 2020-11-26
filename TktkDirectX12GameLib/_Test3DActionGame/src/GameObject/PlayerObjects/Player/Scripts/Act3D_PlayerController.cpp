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
		throw std::runtime_error("Act3D_PlayerController not found Transform3D");
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

	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_Tab))
	{
		lookMostNearEnemy();
	}

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

void Act3D_PlayerController::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::LookToEnemy))
	{
		lookMostNearEnemy();
	}
}

tktk::ComponentPtr<tktk::Transform3D> Act3D_PlayerController::findMostNearEnemyTransform()
{
	auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

	if (playerObject.expired()) return tktk::ComponentPtr<tktk::Transform3D>();

	auto enemyObjects = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	if (std::begin(enemyObjects) == std::end(enemyObjects)) return tktk::ComponentPtr<tktk::Transform3D>();

	auto playerTransform = playerObject->getComponent<tktk::Transform3D>();

	auto minDist = std::numeric_limits<float>::max();

	tktk::ComponentPtr<tktk::Transform3D> result;

	for (const auto& enemyObject : enemyObjects)
	{
		auto enemyTransform = enemyObject->getComponent<tktk::Transform3D>();

		auto dist = tktkMath::Vector3::distance(playerTransform->getWorldPosition(), enemyTransform->getWorldPosition());

		if (dist < minDist)
		{
			result = enemyTransform;
			minDist = dist;
		}
	}
	return result;
}

void Act3D_PlayerController::lookMostNearEnemy()
{
	auto nearEnemyTransform = findMostNearEnemyTransform();

	if (!nearEnemyTransform.expired())
	{
		auto rotateDir = nearEnemyTransform->getWorldPosition() - m_transform->getWorldPosition();

		m_transform->setLocalEulerAngles({ 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
	}
}
