#ifndef ACT3D_FIGHTER_ENEMY_START_RUN_H_
#define ACT3D_FIGHTER_ENEMY_START_RUN_H_

#include <TktkDX12GameLib.h>

// 近接攻撃エネミーのダッシュ移動を開始する処理を行うコンポーネント
class Act3D_FighterEnemyStartRun
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ダッシュが発生するまでの時間
	static constexpr float StartRunTimeSec{ 3.0f };

private:

	// ダッシュを始めるためのタイマー
	float m_startRunSecTimer{ 0.0f };
};
#endif // !ACT3D_FIGHTER_ENEMY_START_RUN_H_