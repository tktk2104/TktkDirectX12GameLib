#include "Sht2D_SpreadBulletEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_SpreadBulletEnemyDamager::start()
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

void Sht2D_SpreadBulletEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// 非アクティブ状態だったら処理を終える
	if (!isActive()) return;

	// ダメージメッセージを受け取ったら
	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージを与える
		m_healthPoint->damage(*attachment.getValuePtr<float>().lock());

		// 死んだら
		if (m_healthPoint->outOfHp())
		{
			getGameObject()->stateDisable(SpreadBulletEnemyState::Alive);
			getGameObject()->stateEnable(SpreadBulletEnemyState::Dead);
		}
	}
}
