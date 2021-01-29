#include "Sht2D_RoteteToObject.h"

#include <TktkMath/MathHelper.h>

Sht2D_RoteteToObject::Sht2D_RoteteToObject(float rotateSpeedPerSecDeg, const tktk::GameObjectPtr& rotateTarget)
	: m_rotateSpeedPerSecDeg(rotateSpeedPerSecDeg)
{
	// 回転対象オブジェクトが存在しなかったら関数を終える
	if (rotateTarget.expired()) return;

	// 回転対象オブジェクトから座標管理コンポーネントを取得する
	m_roteteTargetTransform			= rotateTarget->getComponent<tktk::Transform2D>();
}

void Sht2D_RoteteToObject::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_RoteteToObject not found Transform2D");
	}
}

void Sht2D_RoteteToObject::update()
{
	// 回転対象の座標管理コンポーネントが存在しなかったら関数を終える
	if (m_roteteTargetTransform.expired()) return;

	// 自身->ターゲットのベクトルを計算
	auto selfToTarget = m_roteteTargetTransform->getWorldPosition() - m_transform->getWorldPosition();

	// 回転する角度の最大値
	auto rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToTarget) - m_transform->getWorldRotationDeg();

	// 逆回り補正
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// 回転する角度
	auto rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * m_rotateSpeedPerSecDeg;

	// フレーム毎の移動量に補正
	rotateDist *= tktk::DX12Game::deltaTime();

	// 回転角度制限
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// 回転角度を更新する
	m_transform->addLocalRotationDeg(rotateDist);
}
