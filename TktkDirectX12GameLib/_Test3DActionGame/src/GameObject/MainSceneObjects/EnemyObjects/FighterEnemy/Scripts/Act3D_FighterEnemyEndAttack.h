#ifndef ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_
#define ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// 近距離攻撃エネミーの攻撃状態を終了する処理を行うコンポーネント
class Act3D_FighterEnemyEndAttack
	: public tktk::ComponentBase
{
public:

	Act3D_FighterEnemyEndAttack(float endAttackTimeSec, FighterEnemyState attackType);

public:

	void onEnable();
	void update();

private:

	// 攻撃状態を終了するまでの時間（秒）
	const float				m_endAttackTimeSec;

	// 終了する近接攻撃エネミーの状態
	const FighterEnemyState	m_attackType;

	// 攻撃状態を終了するためのタイマー
	float					m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_FIGHTER_ENEMY_END_ATTACK_H_