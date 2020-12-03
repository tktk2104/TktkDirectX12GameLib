#include "Act3D_ShooterEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_ShooterEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_ShooterEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_ShooterEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// 非アクティブ状態だったら何もしない
	if (!isActive()) return;

	// 受け取ったメッセージが被ダメージメッセージだったら
	if (type.isSame(EventMessageType::Damage))
	{
		// 自身にダメージを与える
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// 死んだら
		if (m_selfParam->outOfHp())
		{
			// 死亡状態を有効にする
			getGameObject()->stateEnable(FighterEnemyState::Dead);

			// 生存状態を無効にする
			getGameObject()->stateDisable(FighterEnemyState::Alive);
		}
		else
		{
			// もし待機状態だったら
			if (getGameObject()->containState(FighterEnemyState::Idle))
			{
				// 歩き状態を有効にする
				getGameObject()->statesEnable({ FighterEnemyState::Move, FighterEnemyState::Walk });

				// 待機状態を無効にする
				getGameObject()->stateDisable(FighterEnemyState::Idle);
			}

			// ダメージ状態を有効にする
			getGameObject()->stateEnable(FighterEnemyState::Damage);

			// 通常状態を無効にする
			getGameObject()->stateDisable(FighterEnemyState::Normal);
		}
	}
}
