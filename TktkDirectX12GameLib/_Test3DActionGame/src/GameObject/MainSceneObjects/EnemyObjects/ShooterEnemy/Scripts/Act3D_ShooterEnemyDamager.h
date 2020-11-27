#ifndef ACT_3D_SHOOTER_ENEMY_DAMAGER_H_
#define ACT_3D_SHOOTER_ENEMY_DAMAGER_H_

#include <TktkDX12GameLib.h>
#include "Act3D_ShooterEnemyParam.h"

// 遠距離攻撃エネミーの被ダメージコンポーネント
class Act3D_ShooterEnemyDamager
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyDamager() = default;

public:

	void start();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment & attachment);

private:

	// 遠距離攻撃エネミーの能力値のコンポーネント
	tktk::ComponentPtr<Act3D_ShooterEnemyParam> m_selfParam;
};
#endif // !ACT_3D_SHOOTER_ENEMY_DAMAGER_H_
