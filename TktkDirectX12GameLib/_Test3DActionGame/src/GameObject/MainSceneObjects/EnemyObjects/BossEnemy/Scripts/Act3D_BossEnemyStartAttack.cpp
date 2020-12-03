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
	// プレイヤーの座標管理コンポーネントが取得できていなければ、
	if (m_playerTransform.expired())
	{
		// プレイヤーオブジェクトを取得する
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// プレイヤーオブジェクトを取得できなければ処理を終える
		if (player.expired()) return;

		// プレイヤーの座標管理コンポーネントを取得する
		m_playerTransform = player->getComponent<tktk::Transform3D>();

		// プレイヤーの座標管理コンポーネントが取得できなければ処理を終える
		if (m_playerTransform.expired()) return;
	}

	// プレイヤー方向へのベクトル
	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	// プレイヤー方向への角度
	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	// プレイヤー方向への角度の差
	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;
	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	// プレイヤーの座標との差
	auto posDist = tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition());

	// 通常攻撃を行う条件が揃っていたら
	if (m_selfParam->canNormalAttack() && posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		// 通常攻撃状態を有効にする
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::NormalAttack });
		
		// 移動状態を無効にする
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		// 攻撃間隔タイマーを通常攻撃の値を使ってリセットする
		m_selfParam->resetNormalAttackIntervelTimer(NormalAttackIntervalTimeSec);
	}

	// ローリング攻撃を行う条件が揃っていたら
	else if (m_selfParam->canRollAttack() && posDist < RollAttackStartRange && std::abs(rotateDist) < RollAttackStartAngleDeg)
	{
		//if (tktkMath::Random::getRandF(0.0f, 1.0f) < RollAttackMissRate)
		//{
		//	getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
		//	getGameObject()->statesDisable({ BossEnemyStateType::Move });
		//}
		//else
		{
			// ローリング攻撃状態を有効にする
			getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::RollAttack });
			
			// 移動状態を無効にする
			getGameObject()->statesDisable({ BossEnemyStateType::Move });
		}

		// 攻撃間隔タイマーをローリング攻撃の値を使ってリセットする
		m_selfParam->resetRollAttackIntervelTimer(RollAttackIntervalTimeSec);
	}

	// ジャンプ攻撃を行う条件が揃っていたら
	else if (m_selfParam->canJumpAttack() && posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		// ジャンプ攻撃状態を有効にする
		getGameObject()->statesEnable({ BossEnemyStateType::Attack, BossEnemyStateType::JumpAttack });
		
		// 移動状態を無効にする
		getGameObject()->statesDisable({ BossEnemyStateType::Move });

		// 攻撃間隔タイマーをジャンプ攻撃の値を使ってリセットする
		m_selfParam->resetJumpAttackIntervelTimer(JumpAttackIntervalTimeSec);
	}
}
