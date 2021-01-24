#include "Sht2D_PlayerMoveScript.h"

#include <stdexcept>

void Sht2D_PlayerMoveScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMoveScript not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMoveScript not found InertialMovement2D");
	}
}

void Sht2D_PlayerMoveScript::update()
{
	auto moveDirection = tktkMath::Vector2::scale(tktk::DX12Game::getMoveInput(), tktkMath::Vector2(1.0f, -1.0f));

	m_inertialMovement->addContinuousForce(moveDirection * MoveSpeedPerSec, 4096.0f);

	auto clampedPos = tktkMath::Vector2::clamp(m_transform->getWorldPosition(), MoveAreaLeftTopPos, MoveAreaRightBottomPos);

	m_transform->setWorldPosition(clampedPos);

	if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_P))m_transform->addWorldRotationDeg(1.0f);
}