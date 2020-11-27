#ifndef ACT_3D_END_ATTACK_H_
#define ACT_3D_END_ATTACK_H_

#include <TktkDX12GameLib.h>
#include "../../../../../Enums/Enums.h"

// プレイヤーの攻撃処理を終了するコンポーネント
class Act3D_PlayerEndAttack
	: public tktk::ComponentBase
{
public:

	explicit Act3D_PlayerEndAttack(float endAttackTime);

public:

	void onEnable();
	void update();

private:

	// 攻撃を終了するまでの時間
	const float				m_endAttackTimeSec;

	// 攻撃を終了するためのタイマー
	float					m_endAttackSecTimer{ 0.0f };
};
#endif // !ACT_3D_END_ATTACK_H_