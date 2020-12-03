#include "Act3D_RotateToPlayerInTime.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../Enums/Enums.h"

Act3D_RotateToPlayerInTime::Act3D_RotateToPlayerInTime(float roteteSpeedPerSecDeg, float rotateEndTimeSec)
	: m_roteteSpeedPerSecDeg(roteteSpeedPerSecDeg)
	, m_rotateEndTimeSec(rotateEndTimeSec)
{
}

void Act3D_RotateToPlayerInTime::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FindPlayer not found Transform3D");
	}
}

void Act3D_RotateToPlayerInTime::onEnable()
{
	// タイマーを初期化する
	m_rotateEndSecTimer = m_rotateEndTimeSec;
}

void Act3D_RotateToPlayerInTime::update()
{
	// タイマーのカウントがゼロだったら処理を終える
	if (m_rotateEndSecTimer < 0.0f) return;

	// タイマーをカウントダウンする
	m_rotateEndSecTimer -= tktk::DX12Game::deltaTime();

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

	// 回転速度を求める
	auto roteteSpeed = m_roteteSpeedPerSecDeg * tktk::DX12Game::deltaTime();

	// 回転角度を求める
	auto rotateWidth = (std::abs(rotateDist) > roteteSpeed) ? (roteteSpeed * tktkMath::MathHelper::sign(rotateDist)) : rotateDist;

	// 自身を回転させる
	m_selfTransform->addLocalEulerAngles(tktkMath::Vector3(0.0f, rotateWidth, 0.0f));
}
