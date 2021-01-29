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
	// 移動方向を移動入力方向から取得する（画面の座標系はｙ軸が反転しているので注意してください）
	tktkMath::Vector2 moveDirection = tktkMath::Vector2::scale(tktk::DX12Game::getMoveInput(), tktkMath::Vector2(1.0f, -1.0f));

	// 継続的な力として慣性移動コンポーネントで力を加える
	m_inertialMovement->addContinuousForce(moveDirection * MoveSpeedPerSec, AccelerationPerSec);

	// 画面外にプレイヤーが出ている可能性を考慮して、クランプする
	tktkMath::Vector2 clampedPos = tktkMath::Vector2::clamp(m_transform->getWorldPosition(), MoveAreaLeftTopPos, MoveAreaRightBottomPos);

	// 画面内補正を行った座標に移動させる
	m_transform->setWorldPosition(clampedPos);
}