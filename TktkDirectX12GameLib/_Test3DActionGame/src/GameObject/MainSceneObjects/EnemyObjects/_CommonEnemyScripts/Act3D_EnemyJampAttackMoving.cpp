#include "Act3D_EnemyJampAttackMoving.h"

Act3D_EnemyJampAttackMoving::Act3D_EnemyJampAttackMoving(float jumpVerticalPower, float jmupVerticalMoveStartTimeSec, float jumpHorizontalSpeedPerSec, float jmupHorizontalMoveTimeSec)
	: m_jumpVerticalPower(jumpVerticalPower)
	, m_jmupVerticalMoveStartTimeSec(jmupVerticalMoveStartTimeSec)
	, m_jumpHorizontalSpeedPerSec(jumpHorizontalSpeedPerSec)
	, m_jmupHorizontalMoveTimeSec(jmupHorizontalMoveTimeSec)
{
}

void Act3D_EnemyJampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found Transform3D");
	}
	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found InertialMovement3D");
	}

}

void Act3D_EnemyJampAttackMoving::onEnable()
{
	// メンバ変数を初期化する
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_EnemyJampAttackMoving::update()
{
	// 垂直移動開始タイマーが指定の値に達していなければ
	if (m_verticalMoveSecTimer < m_jmupVerticalMoveStartTimeSec)
	{
		// タイマーをカウントアップ
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	// 垂直移動を開始する条件が揃っていれば
	else if (!m_afterVerticalMove)
	{
		// 垂直方向に飛び跳ねる
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * m_jumpVerticalPower);

		// 垂直移動後フラグを立てる
		m_afterVerticalMove = true;
	}

	// 水平移動タイマーが指定の値に達していなければ
	if (m_horizontalMoveSecTimer < m_jmupHorizontalMoveTimeSec)
	{
		// タイマーをカウントアップ
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		// 自身の座標管理コンポーネントに移動幅を渡す
		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * m_jumpHorizontalSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}
