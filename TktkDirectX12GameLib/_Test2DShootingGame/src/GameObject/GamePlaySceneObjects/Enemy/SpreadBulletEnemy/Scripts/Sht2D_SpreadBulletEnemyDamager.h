#ifndef SHT_2D_SPREAD_BULLET_ENEMY_DAMAGER_H_
#define SHT_2D_SPREAD_BULLET_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "../../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"

// 拡散弾エネミーのダメージ処理コンポーネント
class Sht2D_SpreadBulletEnemyDamager
	: public tktk::ComponentBase
{
public:

	Sht2D_SpreadBulletEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment & attachment);

private:

	tktk::ComponentPtr<tktk::Transform2D>	m_transform;

	// 拡散弾エネミーの耐久力のコンポーネント
	tktk::ComponentPtr<Sht2D_HealthPoint> m_healthPoint;
};
#endif // !SHT_2D_SPREAD_BULLET_ENEMY_DAMAGER_H_