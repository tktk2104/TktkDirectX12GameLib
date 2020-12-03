#include "Act3D_PlayerDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerDamager::start()
{
	m_selfParam = getComponent<Act3D_PlayerParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_PlayerDamager not found Act3D_PlayerParam");
	}
}

void Act3D_PlayerDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// 非アクティブ状態だったら処理を終える
	if (!isActive()) return;

	// ダメージメッセージを受け取ったら
	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージを与える
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// 死んだら
		if (m_selfParam->outOfHp())
		{
			// 死亡状態を有効にする
			getGameObject()->stateEnable(PlayerStateType::Dead);

			// 生存状態を無効にする
			getGameObject()->stateDisable(PlayerStateType::Alive);
		}
		else
		{
			// ダメージ状態を有効にする
			getGameObject()->stateEnable(PlayerStateType::Damage);

			// 通常状態を無効にする
			getGameObject()->stateDisable(PlayerStateType::Normal);
		}
	}
}
