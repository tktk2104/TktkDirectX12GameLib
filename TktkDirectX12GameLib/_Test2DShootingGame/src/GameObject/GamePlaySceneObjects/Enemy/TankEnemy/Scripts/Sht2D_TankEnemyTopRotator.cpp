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
	auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

 	if (player.expired()) return;

	auto playerTransform = player->getComponent<tktk::Transform2D>();

	if (playerTransform.expired()) return;

	// Ž©g->ƒvƒŒƒCƒ„[‚ÌƒxƒNƒgƒ‹‚ðŒvŽZ
	auto selfToPlayer = playerTransform->getWorldPosition() + TargetOffset - m_transform->getWorldPosition();

	// ‰ñ“]‚·‚éŠp“x‚ÌÅ‘å’l
	auto rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToPlayer) - m_transform->getWorldRotationDeg();

	// ‹t‰ñ‚è•â³
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// ‰ñ“]‚·‚éŠp“x
	auto rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * RotateSpeedPerSecDeg;

	// ƒtƒŒ[ƒ€–ˆ‚ÌˆÚ“®—Ê‚É•â³
	rotateDist *= tktk::DX12Game::deltaTime();

	// ‰ñ“]Šp“x§ŒÀ
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// ‰ñ“]Šp“x‚ðXV‚·‚é
	m_transform->addLocalRotationDeg(rotateDist);
}