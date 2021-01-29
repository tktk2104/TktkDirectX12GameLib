#ifndef SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_
#define SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_

#include <TktkDX12GameLib.h>

// プレイヤーボムのアクティブタイマーコンポーネント
class Sht2D_PlayerBombActiveTimer
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerBombActiveTimer(float activeTimeSec);

public:

	void update();

private:

	// アクティブタイマー（秒）
	float m_activeSecTimer;
};
#endif // !SHT_2D_PLAYER_BOMB_ACTIVE_TIMER_H_