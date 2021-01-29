#ifndef SHT_2D_PLAYER_MISSILE_EXPLODE_H_
#define SHT_2D_PLAYER_MISSILE_EXPLODE_H_

#include <TktkDX12GameLib.h>

// プレイヤーミサイル起爆用コンポーネント
class Sht2D_PlayerMissileExplode
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerMissileExplode(float startHitPower, float stayHitPowerPerSec);

public:

	void start();

public:

	void explode();

private:

	// 接触開始時ダメージ
	float m_startHitPower;

	// 毎秒の接触中ダメージ
	float m_stayHitPowerPerSec;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !SHT_2D_PLAYER_MISSILE_EXPLODE_H_