#ifndef ACT_3D_INPUT_TO_START_ATTACK_H_
#define ACT_3D_INPUT_TO_START_ATTACK_H_

#include <TktkDX12GameLib.h>

// 入力によって攻撃を開始するコンポーネント
class Act3D_InputToStartAttack
	: public tktk::ComponentBase
{
public:

	Act3D_InputToStartAttack() = default;

public:

	void update();

private:

	// 攻撃のインターバル
	constexpr static float AttackIntervalTimeSec{ 0.7f };

private:

	// 攻撃間隔を管理するコンポーネント
	float m_attackIntervelSecTimer{ 0.0f };
};
#endif // !ACT_3D_INPUT_TO_START_ATTACK_H_