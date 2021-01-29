#ifndef EXPLOSION_2D_SCRIPT_H_
#define EXPLOSION_2D_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_ExplosionScript
	: public tktk::ComponentBase
{
public:

	// 一定時間後に自身を殺すコンポーネント
	explicit Sht2D_ExplosionScript(float effectEndTimeSec);
	~Sht2D_ExplosionScript() = default;

public:

	// 毎フレーム呼ばれる
	void update();

private:

	// 爆発終了タイマー（秒）
	float m_effectEndSecTimer;
};
#endif // !EXPLOSION_2D_SCRIPT_H_