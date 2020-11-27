#ifndef ACT_3D_FIGHTER_ENEMY_DAMAGER_H_
#define ACT_3D_FIGHTER_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_FighterEnemyParam.h"

// �ߐڍU���G�l�~�[�̃_���[�W�����R���|�[�l���g
class Act3D_FighterEnemyDamager
	: public tktk::ComponentBase
{
public:
	
	Act3D_FighterEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);

private:

	// �ߐڍU���G�l�~�[�̔\�͒l�̃R���|�[�l���g
	tktk::ComponentPtr<Act3D_FighterEnemyParam> m_selfParam;
};
#endif // !ACT_3D_FIGHTER_ENEMY_DAMAGER_H_