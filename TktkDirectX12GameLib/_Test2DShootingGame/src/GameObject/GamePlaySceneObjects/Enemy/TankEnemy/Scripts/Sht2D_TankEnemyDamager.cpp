#include "Sht2D_TankEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_TankEnemyDamager::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyDamager not found Transform2D");
	}

	m_healthPoint = getComponent<Sht2D_HealthPoint>();

	if (m_healthPoint.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyDamager not found Sht2D_HealthPoint");
	}
}

void Sht2D_TankEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// 非アクティブ状態だったら処理を終える
	if (!isActive()) return;

	// ダメージメッセージを受け取ったら
	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージを与える
		m_healthPoint->damage(*attachment.getValuePtr<float>().lock());

		// 自身の体力が０以下だったら
		if (m_healthPoint->outOfHp())
		{
			// 自身の状態を生存状態から死亡状態に遷移させる
			getGameObject()->stateDisable(TankEnemyStateTypes::Alive);
			getGameObject()->stateEnable(TankEnemyStateTypes::Dead);
		}
	}
}
