#ifndef ACT_3D_PLAYER_END_DODGE_H_
#define ACT_3D_PLAYER_END_DODGE_H_

#include <TktkDX12GameLib.h>

// プレイヤーの回避状態を終了するコンポーネント
class Act3D_PlayerEndDodge
	: public tktk::ComponentBase
{
public:

	void start();
	void onEnable();
	void update();

private:

	// 回避状態が終わるまでの時間
	static constexpr float EndDodgeTimeSec{ 1.0f };

private:

	// 回避状態を終了するためのタイマー
	float m_endDodgeSecTimer{ 0.0f };

	// メッシュ描画コンポーネント
	tktk::ComponentPtr<tktk::MeshDrawer>	m_meshDrawer;
};
#endif // !ACT_3D_PLAYER_END_DODGE_H_