#ifndef ACT_3D_END_DAMAGE_H_
#define ACT_3D_END_DAMAGE_H_

#include <TktkDX12GameLib.h>

// プレイヤーのダメージ状態を終了させるコンポーネント
class Act3D_PlayerEndDamage
	: public tktk::ComponentBase
{
public:

	void onEnable();
	void update();

private:

	// ダメージ状態が終わるまでの時間
	constexpr static float EndDamageTimeSec{ 0.6f };

private:

	// ダメージ状態を終了させるためのタイマー
	float m_endDamageSecTimer{ 0.0f };
};
#endif // !ACT_3D_END_DAMAGE_H_