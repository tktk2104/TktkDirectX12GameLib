#include "Act3D_InputToStartDodge.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartDodge::start()
{
	m_meshDrawer = getComponent<tktk::MeshDrawer>();

	if (m_meshDrawer.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found MeshDrawer");
	}

	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found Transform3D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found InertialMovement3D");
	}
}

void Act3D_InputToStartDodge::update()
{
	// 回避間隔タイマーがゼロではなければ
	if (m_dodgeIntervelSecTimer > 0.0f)
	{
		// タイマーをカウントダウン
		m_dodgeIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// 回避ボタンが押されていたら
	if (tktk::DX12Game::isTrigger(CommandId::Dodge))
	{
		// プレイヤーの移動入力を取得する
		auto inputMoveVec = tktk::DX12Game::moveVec();

		// 移動方向を取得する
		auto moveDir	= tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y) * m_transform->getWorldRotation();

		// 回転方向を取得する
		auto rotateDir	= tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y);

		// メッシュのローカル回転を移動方向の方を向かせる
		m_meshDrawer->setBaseRotation(tktkMath::Quaternion::createFromEulerAngle(
			{ 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up) + 180.0f, 0.0f }
		));

		// 回避移動を始める
		m_inertialMovement->addMomentarilyForce(moveDir.normalized() * DodgeMovePower);

		// 回避状態にする
		getGameObject()->stateEnable(PlayerStateType::Dodge);

		// 移動状態を切る
		getGameObject()->stateDisable(PlayerStateType::Move);

		// 回避のインターバルタイマーをリセットする
		m_dodgeIntervelSecTimer = DodgeIntervalTimeSec;
	}
}