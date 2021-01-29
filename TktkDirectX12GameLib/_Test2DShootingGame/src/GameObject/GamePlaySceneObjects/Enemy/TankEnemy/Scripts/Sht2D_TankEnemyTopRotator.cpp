#include "Sht2D_TankEnemyTopRotator.h"

#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

void Sht2D_TankEnemyTopRotator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyTopRotator not found Transform2D");
	}
}

void Sht2D_TankEnemyTopRotator::update()
{
	// プレイヤーオブジェクトを取得
	tktk::GameObjectPtr player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

	// プレイヤーオブジェクトが取得できなければ関数を終える
 	if (player.expired()) return;

	// プレイヤーの座標管理コンポーネントを取得
	tktk::ComponentPtr<tktk::Transform2D> playerTransform = player->getComponent<tktk::Transform2D>();

	// プレイヤーの座標管理コンポーネントが取得できなければ関数を終える
	if (playerTransform.expired()) return;

	// 自身->プレイヤーのベクトルを計算
	tktkMath::Vector2 selfToPlayer = playerTransform->getWorldPosition() + TargetOffset - m_transform->getWorldPosition();

	// 回転する角度の最大値
	float rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToPlayer) - m_transform->getWorldRotationDeg();

	// 逆回り補正
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// 回転する角度
	float rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * RotateSpeedPerSecDeg;

	// フレーム毎の移動量に補正
	rotateDist *= tktk::DX12Game::deltaTime();

	// 回転角度制限
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// 回転角度を更新する
	m_transform->addLocalRotationDeg(rotateDist);
}