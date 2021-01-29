#ifndef SHT_2D_DAMAGE_POWER_H_
#define SHT_2D_DAMAGE_POWER_H_

#include <TktkDX12GameLib.h>

// 接触時のダメージパワーコンポーネント
class Sht2D_DamagePower
	: public tktk::ComponentBase
{
public:

	Sht2D_DamagePower(float startHitPower, float stayHitPowerPerSec);

public:

	// 接触開始時ダメージを取得する
	float getStartHitPower() const;

	// 毎秒の接触中ダメージを取得する
	float getStayHitPowerPerSec() const;

private:

	// 接触開始時ダメージ
	float m_startHitPower;

	// 接触中ダメージ（毎秒）
	float m_stayHitPowerPerSec;
};
#endif // !SHT_2D_DAMAGE_POWER_H_