#ifndef ACT_3D_INPUT_TO_START_DODGE_H_
#define ACT_3D_INPUT_TO_START_DODGE_H_

#include <TktkDX12GameLib.h>

// 入力によって回避行動を開始するコンポーネント
class Act3D_InputToStartDodge
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartDodge() = default;

public:

	void start();
	void update();

private:

	// 回避のインターバル
	constexpr static float DodgeIntervalTimeSec{ 0.7f };

	// 回避移動の初速
	constexpr static float DodgeMovePower{ 6.0f };

private:

	// 回避間隔を管理するタイマー
	float m_dodgeIntervelSecTimer{ 0.0f };

	// メッシュ描画コンポーネント
	tktk::ComponentPtr<tktk::MeshDrawer>			m_meshDrawer;

	// 座標管理コンポーネント
	tktk::ComponentPtr<tktk::Transform3D>			m_transform;

	// 慣性移動コンポーネント
	tktk::ComponentPtr<tktk::InertialMovement3D>	m_inertialMovement;
};
#endif // !ACT_3D_INPUT_TO_START_DODGE_H_