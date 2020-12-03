#ifndef ACT_3D_BOSS_ENEMY_DAMAGER_H_
#define ACT_3D_BOSS_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_BossEnemyParam.h"

// �{�X�G�l�~�[�̔�_���[�W�����R���|�[�l���g
class Act3D_BossEnemyDamager
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment & attachment);

private:

	// �{�X�G�l�~�[�̔\�͒l
	tktk::ComponentPtr<Act3D_BossEnemyParam> m_selfParam;
};
#endif // !ACT_3D_BOSS_ENEMY_DAMAGER_H_