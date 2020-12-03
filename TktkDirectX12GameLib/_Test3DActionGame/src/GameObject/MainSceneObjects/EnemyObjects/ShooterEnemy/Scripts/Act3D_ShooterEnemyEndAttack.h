#ifndef ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_
#define ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// 遠距離攻撃エネミーの攻撃終了コンポーネント
class Act3D_ShooterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_ShooterEnemyEndAttack(float endAttackTimeSec, ShooterEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	// 攻撃が終了するまでの時間（秒）
	const float					m_endAttackTimeSec;

	// 終了する遠距離攻撃エネミーの状態
	const ShooterEnemyStateType	m_attackType;

	// 攻撃を終了するためのタイマー
	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_SHOOTER_ENEMY_END_ATTACK_H_
