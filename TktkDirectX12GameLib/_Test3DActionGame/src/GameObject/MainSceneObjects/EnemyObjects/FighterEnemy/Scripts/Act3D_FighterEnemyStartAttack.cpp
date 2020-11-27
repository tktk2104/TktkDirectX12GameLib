#include "Act3D_FighterEnemyStartAttack.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

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
	// 攻撃間隔タイマーのカウントがゼロでなければ
	if (m_attackIntervelSecTimer > 0.0f)
	{
		// タイマーのカウントダウンを行い、処理を終える
		m_attackIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

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

	// 自身からプレイヤーへの方向を計算する
	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	// プレイヤー方向へのｙ軸基準の回転の差を取得する（度数法）
	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	// 回転するべき角度を取得する
	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;

	// 回転角度が180度を越えていたら逆回転にする
	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	// 自身とプレイヤーの座標の差を計算する
	auto posDist = tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition());

	// 通常攻撃を行う条件を満たしていれば
	if (posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		// 通常攻撃状態を有効にする
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::Punch });
		
		// 移動状態を無効にする
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		// 攻撃間隔タイマーを通常攻撃の値で初期化する
		m_attackIntervelSecTimer = NormalAttackIntervalTimeSec;
	}

	// ジャンプ攻撃を行う条件を満たしていれば
	else if (posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		// ジャンプ攻撃状態を有効にする
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::JumpAttack });
		
		// 移動状態を無効にする
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		// 攻撃間隔タイマーをジャンプ攻撃の値で初期化する
		m_attackIntervelSecTimer = JumpAttackIntervalTimeSec;
	}
}
