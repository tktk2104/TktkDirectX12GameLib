#ifndef ACT_3D_BOSS_ENEMY_END_DOWN_H_
#define ACT_3D_BOSS_ENEMY_END_DOWN_H_

#include <TktkDX12GameLib.h>

// ボスエネミーのダウン状態を終了する処理を行うコンポーネント
class Act3D_BossEnemyEndDown
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyEndDown() = default;

public:

	void onEnable();
	void update();

private:

	// 起き上がる終わるまでの時間
	constexpr static float EndDownTimeSec{ 0.8f };

private:

	// ダウン状態を終了する処理を行うためのタイマー
	float m_endDownUpSecTimer{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_END_DOWN_H_