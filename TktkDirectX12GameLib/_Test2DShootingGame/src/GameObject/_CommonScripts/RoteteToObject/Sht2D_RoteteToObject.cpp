#include "Sht2D_RoteteToObject.h"

#include <TktkMath/MathHelper.h>

Sht2D_RoteteToObject::Sht2D_RoteteToObject(float rotateSpeedPerSecDeg, const tktk::GameObjectPtr& rotateTarget)
	: m_rotateSpeedPerSecDeg(rotateSpeedPerSecDeg)
{
	if (rotateTarget.expired()) return;

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
	if (m_roteteTargetTransform.expired()) return;

	// Ž©g->ƒ^[ƒQƒbƒg‚ÌƒxƒNƒgƒ‹‚ðŒvŽZ
	auto selfToTarget = m_roteteTargetTransform->getWorldPosition() - m_transform->getWorldPosition();

	// ‰ñ“]‚·‚éŠp“x‚ÌÅ‘å’l
	auto rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToTarget) - m_transform->getWorldRotationDeg();

	// ‹t‰ñ‚è•â³
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// ‰ñ“]‚·‚éŠp“x
	auto rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * m_rotateSpeedPerSecDeg;

	// ƒtƒŒ[ƒ€–ˆ‚ÌˆÚ“®—Ê‚É•â³
	rotateDist *= tktk::DX12Game::deltaTime();

	// ‰ñ“]Šp“x§ŒÀ
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// ‰ñ“]Šp“x‚ðXV‚·‚é
	m_transform->addLocalRotationDeg(rotateDist);
}
