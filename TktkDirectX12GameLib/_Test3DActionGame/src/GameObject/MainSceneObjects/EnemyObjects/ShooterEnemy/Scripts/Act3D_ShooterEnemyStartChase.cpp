#include "Act3D_ShooterEnemyStartChase.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

void Act3D_ShooterEnemyStartChase::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_ShooterEnemyStartChase not found Transform3D");
	}
}

void Act3D_ShooterEnemyStartChase::update()
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

	// 自身からプレイヤーへの方向を計算する
	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	// プレイヤー方向へのｙ軸基準の回転の差を取得する（度数法）
	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	// 回転するべき角度を取得する
	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;

	// 回転角度が180度を越えていたら逆回転にする
	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	// プレイヤーを見つける条件を満たしていたら
	if (tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition()) < FindPlayerRange && std::abs(rotateDist) < FindPlayerAngleDeg)
	{
		// 移動状態を有効にする
		getGameObject()->stateEnable(ShooterEnemyStateType::Move);

		// 待機状態を無効にする
		getGameObject()->stateDisable(ShooterEnemyStateType::Idle);
	}
}
