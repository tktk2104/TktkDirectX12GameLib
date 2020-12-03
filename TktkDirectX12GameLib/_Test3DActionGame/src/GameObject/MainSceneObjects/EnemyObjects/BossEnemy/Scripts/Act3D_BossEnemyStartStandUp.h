#ifndef ACT_3D_BOSS_ENEMY_START_STAND_UP_H_
#define ACT_3D_BOSS_ENEMY_START_STAND_UP_H_

#include <TktkDX12GameLib.h>

// ボスエネミーの起き上がり処理を行うコンポーネント
class Act3D_BossEnemyStartStandUp
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartStandUp() = default;

public:

	void onEnable();
	void update();

private:

	// 起き上がるまでの時間
	constexpr static float StartStandUpTimeSec{ 5.0f };

private:

	// 起き上がる処理を行うタイマー
	float m_startStandUpSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_START_STAND_UP_H_