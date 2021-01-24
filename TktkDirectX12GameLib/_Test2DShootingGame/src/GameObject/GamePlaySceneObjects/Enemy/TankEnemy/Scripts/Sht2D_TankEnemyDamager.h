#ifndef SHT_2D_TANK_ENEMY_DAMAGER_H_
#define SHT_2D_TANK_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "../../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"

// ��ԃG�l�~�[�̃_���[�W�����R���|�[�l���g
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

	// ��ԃG�l�~�[�̑ϋv�͂̃R���|�[�l���g
	tktk::ComponentPtr<Sht2D_HealthPoint> m_healthPoint;
};
#endif // !SHT_2D_TANK_ENEMY_DAMAGER_H_
