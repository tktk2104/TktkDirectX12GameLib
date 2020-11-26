#include "Act3D_PlayerEndDodge.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerEndDodge::start()
{
	m_meshDrawer = getComponent<tktk::MeshDrawer>();

	if (m_meshDrawer.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found MeshDrawer");
	}
}

void Act3D_PlayerEndDodge::onEnable()
{
	// タイマーを初期化
	m_endDodgeSecTimer = EndDodgeTimeSec;
}

void Act3D_PlayerEndDodge::update()
{
	if (m_endDodgeSecTimer < 0.0f)
	{
		// 通常・移動状態を有効にする
		getGameObject()->statesEnable({ PlayerStateType::Normal, PlayerStateType::Move });

		// 回避状態を無効にする
		getGameObject()->stateDisable(PlayerStateType::Dodge);

		// メッシュのローカル回転を元に戻す
		m_meshDrawer->setBaseRotation(tktkMath::Quaternion::createFromEulerAngle({0.0f, 180.0f, 0.0f}));
		return;
	}

	// タイマーを更新する
	m_endDodgeSecTimer -= tktk::DX12Game::deltaTime();
}
