#include "Act3D_FighterEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_FighterEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_FighterEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージを与える
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
				getGameObject()->statesEnable({FighterEnemyState::Move, FighterEnemyState::Walk});

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
