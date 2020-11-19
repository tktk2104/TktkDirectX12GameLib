#include "Act3D_FighterEnemyStartAttack.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartAttack::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyStartAttack not found Transform3D");
	}
}

void Act3D_FighterEnemyStartAttack::update()
{
	if (m_attackIntervelSecTimer > 0.0f)
	{
		m_attackIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	if (m_playerTransform.expired())
	{
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		if (player.expired()) return;

		m_playerTransform = player->getComponent<tktk::Transform3D>();

		if (m_playerTransform.expired()) return;
	}

	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;

	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	auto posDist = tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition());

	if (posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::Punch });
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		m_attackIntervelSecTimer = NormalAttackIntervalTimeSec;
	}

	else if (posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::JumpAttack });
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		m_attackIntervelSecTimer = JumpAttackIntervalTimeSec;
	}
}
