#ifndef ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_
#define ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_

#include <TktkDX12GameLib.h>

// 入力によって二段目攻撃を開始するコンポーネント
class Act3D_InputToStartComboAttack
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartComboAttack() = default;

public:

	void onEnable();
	void update();

private:

	// 二段目攻撃への遷移を無効にする時間（秒）
	constexpr static float InvalidStateChangeTimeSec{ 0.45f };

private:

	// 二段目攻撃への遷移を無効にする時間を管理するタイマー
	float	m_invalidStateChangeSecTimer	{ 0.0f };

	// 入力後状態かのフラグ
	bool	m_afterInput			{ false };
};
#endif // !ACT_3D_INPUT_TO_START_COMBO_ATTACK_H_