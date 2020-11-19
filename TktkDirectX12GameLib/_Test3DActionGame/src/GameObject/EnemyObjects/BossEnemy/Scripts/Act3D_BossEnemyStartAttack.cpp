#include "Act3D_BossEnemyStartAttack.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include <TktkMath/MathHelper.h>
#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyStartAttack::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyStartAttack not found Transform3D");
	}
}

void Act3D_BossEnemyStartAttack::update()
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

	// 通常攻撃を行う条件が揃っていたら
	if (posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::NormalAttack });
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		m_attackIntervelSecTimer = NormalAttackIntervalTimeSec;
	}

	// ローリング攻撃を行う条件が揃っていたら
	else if (posDist < RollAttackStartRange && std::abs(rotateDist) < RollAttackStartAngleDeg)
	{
		if (tktkMath::Random::getRandF(0.0f, 1.0f) < RollAttackMissRate)
		{
			getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
			getGameObject()->statesDisable({ BossEnemyStateType::Move });
		}
		else
		{
			getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::RollAttack });
			getGameObject()->statesDisable({ BossEnemyStateType::Move });
		}
		
		m_attackIntervelSecTimer = RollAttackIntervalTimeSec;
	}

	// ジャンプ攻撃を行う条件が揃っていたら
	else if (posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::JumpAttack });
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		m_attackIntervelSecTimer = JumpAttackIntervalTimeSec;
	}
}
