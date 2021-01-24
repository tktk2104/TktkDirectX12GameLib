#ifndef SHT_2D_TANK_ENEMY_DAMAGER_H_
#define SHT_2D_TANK_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "../../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"

// 戦車エネミーのダメージ処理コンポーネント
class Sht2D_TankEnemyDamager
	: public tktk::ComponentBase
{
public:

	Sht2D_TankEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);

private:

	tktk::ComponentPtr<tktk::Transform2D>	m_transform;

	// 戦車エネミーの耐久力のコンポーネント
	tktk::ComponentPtr<Sht2D_HealthPoint> m_healthPoint;
};
#endif // !SHT_2D_TANK_ENEMY_DAMAGER_H_
