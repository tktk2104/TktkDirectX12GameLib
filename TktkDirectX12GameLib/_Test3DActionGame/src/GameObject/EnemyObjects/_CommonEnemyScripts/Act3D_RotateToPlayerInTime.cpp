#include "Act3D_RotateToPlayerInTime.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../Enums/Enums.h"

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
	m_rotateEndSecTimer = m_rotateEndTimeSec;
}

void Act3D_RotateToPlayerInTime::update()
{
	if (m_rotateEndSecTimer < 0.0f) return;

	m_rotateEndSecTimer -= tktk::DX12Game::deltaTime();

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

	auto roteteSpeed = m_roteteSpeedPerSecDeg * tktk::DX12Game::deltaTime();

	auto rotateWidth = (std::abs(rotateDist) > roteteSpeed) ? (roteteSpeed * tktkMath::MathHelper::sign(rotateDist)) : rotateDist;

	m_selfTransform->addLocalEulerAngles(tktkMath::Vector3(
		0.0f,
		rotateWidth,
		0.0f
	));
}
