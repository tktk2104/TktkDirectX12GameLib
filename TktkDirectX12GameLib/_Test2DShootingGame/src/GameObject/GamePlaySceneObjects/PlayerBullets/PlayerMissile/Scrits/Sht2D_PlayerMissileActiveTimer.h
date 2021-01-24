#ifndef SHT_2D_PLAYER_MISSILE_ACTIVE_TIMER_H_
#define SHT_2D_PLAYER_MISSILE_ACTIVE_TIMER_H_

#include <TktkDX12GameLib.h>

// プレイヤーミサイルのアクティブタイマーコンポーネント
class Sht2D_PlayerMissileActiveTimer
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerMissileActiveTimer(float activeTimeSec);

public:

	void update();

private:

	float m_activeTimeSec;
	float m_activeSecTimer{ 0.0f };
};
#endif // !SHT_2D_PLAYER_MISSILE_ACTIVE_TIMER_H_