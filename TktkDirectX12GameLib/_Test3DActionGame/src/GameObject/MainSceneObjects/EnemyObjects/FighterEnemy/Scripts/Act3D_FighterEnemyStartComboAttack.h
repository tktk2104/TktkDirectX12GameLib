#ifndef ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_
#define ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

// 近接攻撃エネミーのコンボ攻撃を始めるための処理を行うコンポーネント
class Act3D_FighterEnemyStartComboAttack
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// コンボ攻撃が発生するまでの時間
	constexpr static float StartComboTimeSec{ 1.0f };

private:

	// コンボ攻撃を開始するためのタイマー
	float m_startComboSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_COMBO_ATTACK_H_