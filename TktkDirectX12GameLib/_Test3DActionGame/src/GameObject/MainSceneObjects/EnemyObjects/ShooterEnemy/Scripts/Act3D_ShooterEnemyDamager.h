#ifndef ACT_3D_SHOOTER_ENEMY_DAMAGER_H_
#define ACT_3D_SHOOTER_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_ShooterEnemyParam.h"

// �������U���G�l�~�[�̔�_���[�W�R���|�[�l���g
class Act3D_ShooterEnemyDamager
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment & attachment);

private:

	// �������U���G�l�~�[�̔\�͒l�̃R���|�[�l���g
	tktk::ComponentPtr<Act3D_ShooterEnemyParam> m_selfParam;
};
#endif // !ACT_3D_SHOOTER_ENEMY_DAMAGER_H_
