#ifndef ACT_3D_BOSS_ENEMY_DAMAGER_H_
#define ACT_3D_BOSS_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_BossEnemyParam.h"

class Act3D_BossEnemyDamager
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment & attachment);

private:

	tktk::ComponentPtr<Act3D_BossEnemyParam> m_selfParam;
};
#endif // !ACT_3D_BOSS_ENEMY_DAMAGER_H_