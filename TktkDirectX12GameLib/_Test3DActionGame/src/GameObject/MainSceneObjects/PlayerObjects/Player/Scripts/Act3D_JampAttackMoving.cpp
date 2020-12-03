#include "Act3D_JampAttackMoving.h"

void Act3D_JampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found Transform3D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found InertialMovement3D");
	}
}

void Act3D_JampAttackMoving::onEnable()
{
	// メンバ変数を初期化する
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_JampAttackMoving::update()
{
	// 垂直移動開始タイマーが指定の値に達していなければ
	if (m_verticalMoveSecTimer < JmupVerticalMoveStartTimeSec)
	{
		// タイマーをカウントアップ
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	// 垂直移動を開始する条件が揃っていれば
	else if (!m_afterVerticalMove)
	{
		// 垂直方向に飛び跳ねる
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * JumpVerticalPower);

		// 垂直移動後フラグを立てる
		m_afterVerticalMove = true;
	}

	// 水平移動タイマーが指定の値に達していなければ
	if (m_horizontalMoveSecTimer < JmupHorizontalMoveTimeSec)
	{
		// タイマーをカウントアップ
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		// 水平移動速度
		auto jumpSpeedPerSec = JumpHorizontalSpeedPerSec;

		// 前方向への入力が一定以下だったら速度を減速する
		if (tktk::DX12Game::moveVec().y < 0.5f) jumpSpeedPerSec *= 0.5f;

		// 自身の座標管理コンポーネントに移動幅を渡す
		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * jumpSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}