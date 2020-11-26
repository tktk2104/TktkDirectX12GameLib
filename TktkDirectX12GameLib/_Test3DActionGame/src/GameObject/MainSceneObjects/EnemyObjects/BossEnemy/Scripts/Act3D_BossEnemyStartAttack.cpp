#include "Act3D_BossEnemyStartAttack.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyStartAttack::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_BossEnemyStartAttack not found Transform3D");
	}

	m_selfParam = getComponent<Act3D_BossEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_BossEnemyStartAttack not found Act3D_BossEnemyParam");
	}
}

void Act3D_BossEnemyStartAttack::update()
{
	if (m_playerTransform.expired())
	{
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		if (player.expired()) return;

		m_playerTransform = player->getComponent<tktk::Transform3D>();

		if (m_playerTransform.expired()) return;
	}

	// �v���C���[�����ւ̃x�N�g��
	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	// �v���C���[�����ւ̊p�x
	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	// �v���C���[�����ւ̊p�x�̍�
	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;
	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	// �v���C���[�̍��W�Ƃ̍�
	auto posDist = tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition());

	// �ʏ�U�����s�������������Ă�����
	if (m_selfParam->canNormalAttack() && posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::NormalAttack });
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		m_selfParam->resetNormalAttackIntervelTimer(NormalAttackIntervalTimeSec);
	}

	// ���[�����O�U�����s�������������Ă�����
	else if (m_selfParam->canRollAttack() && posDist < RollAttackStartRange && std::abs(rotateDist) < RollAttackStartAngleDeg)
	{
		//if (tktkMath::Random::getRandF(0.0f, 1.0f) < RollAttackMissRate)
		//{
		//	getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
		//	getGameObject()->statesDisable({ BossEnemyStateType::Move });
		//}
		//else
		{
			getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::RollAttack });
			getGameObject()->statesDisable({ BossEnemyStateType::Move });
		}
		m_selfParam->resetRollAttackIntervelTimer(RollAttackIntervalTimeSec);
	}

	// �W�����v�U�����s�������������Ă�����
	else if (m_selfParam->canJumpAttack() && posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::JumpAttack });
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		m_selfParam->resetJumpAttackIntervelTimer(JumpAttackIntervalTimeSec);
	}
}
