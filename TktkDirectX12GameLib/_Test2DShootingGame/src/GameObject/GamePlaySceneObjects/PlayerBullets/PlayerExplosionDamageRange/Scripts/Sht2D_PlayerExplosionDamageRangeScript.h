#ifndef SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_
#define SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 一定時間後に自身を殺すコンポーネント
class Sht2D_PlayerExplosionDamageRangeScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec);
	~Sht2D_PlayerExplosionDamageRangeScript() = default;

public:

	// 毎フレーム呼ばれる
	void update();

private:

	// 攻撃範囲消滅タイマー（秒）
	float m_deadSecTimer;
};
#endif // !SHT_2D_PLAYER_EXPLOSION_DAMAGE_RANGE_SCRIPT_H_