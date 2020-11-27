#ifndef ACT_3D_BOSS_ENEMY_END_ATTACK_H_
#define ACT_3D_BOSS_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// ボスエネミーの攻撃状態を終了するための処理を行うコンポーネント
class Act3D_BossEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndAttack(float endAttackTimeSec, BossEnemyStateType attackType);

public:

	void onEnable();
	void update();

private:

	// 攻撃状態を終了するまでのタイマー
	const float					m_endAttackTimeSec;

	// 終了する攻撃状態の種類
	const BossEnemyStateType	m_attackType;

	// 攻撃状態を終了する処理を行う為のタイマー
	float						m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_ATTACK_H_