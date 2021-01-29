#include "Sht2D_DoubleSideMove.h"

Sht2D_DoubleSideMove::Sht2D_DoubleSideMove(float moveSpeedPerSec, float accelerationPerSec, float minXPos, float maxXPos)
	: m_moveSpeedPerSec(moveSpeedPerSec)
	, m_accelerationPerSec(accelerationPerSec)
	, m_minXPos(minXPos)
	, m_maxXPos(maxXPos)
{
}

void Sht2D_DoubleSideMove::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_MoveForward not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Sht2D_MoveForward not found InertialMovement2D");
	}
}

void Sht2D_DoubleSideMove::update()
{
	// 現在のｘ座標が左側の折り返し地点を過ぎていたら、反転移動フラグを折る
	if (m_transform->getWorldPosition().x < m_minXPos) m_isInversion = false;

	// 現在のｘ座標が右側の折り返し地点を過ぎていたら、反転移動フラグを立てる
	if (m_transform->getWorldPosition().x > m_maxXPos) m_isInversion = true;

	// 移動方向に継続的に加速する
	m_inertialMovement->addContinuousForce(tktkMath::Vector2_v::right * m_moveSpeedPerSec * (m_isInversion ? -1.0f : 1.0f), m_accelerationPerSec);
}
