#include "Act3D_BossEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_BossEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_BossEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// 非アクティブ状態だったら処理を終える
	if (!isActive()) return;

	// 被ダメージ通知を受け取ったら
	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージを与える
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// 死んだら
		if (m_selfParam->outOfHp())
		{
			// 死亡状態を有効にする
			getGameObject()->stateEnable(BossEnemyStateType::Dead);

			// 生存状態を無効にする
			getGameObject()->stateDisable(BossEnemyStateType::Alive);
		}
		else
		{
			// ダメージ状態を有効にする
			getGameObject()->stateEnable(BossEnemyStateType::Damage);
		}
	}
}