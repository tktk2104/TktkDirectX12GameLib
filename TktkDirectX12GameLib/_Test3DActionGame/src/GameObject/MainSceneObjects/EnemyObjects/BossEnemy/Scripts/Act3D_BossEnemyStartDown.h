#ifndef ACT_3D_BOSS_ENEMY_START_DOWN_H_
#define ACT_3D_BOSS_ENEMY_START_DOWN_H_

#include <TktkDX12GameLib.h>

// ボスエネミーのダウン状態を開始する処理を行うためのコンポーネント
class Act3D_BossEnemyStartDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyStartDown() = default;

public:

	void onEnable();
	void update();

private:

	// ダウン状態になるまでの時間
	constexpr static float StartDownTimeSec{ 2.0f };

private:

	// ダウン状態を開始する処理を行うためのタイマー
	float m_startDownSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_START_DOWN_H_
