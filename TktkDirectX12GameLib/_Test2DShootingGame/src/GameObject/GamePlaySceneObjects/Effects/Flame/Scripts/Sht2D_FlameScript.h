#ifndef SHT_2D_FLAME_SCRIPT_H_
#define SHT_2D_FLAME_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 炎エフェクトのアニメーションコンポーネント
class Sht2D_FlameScript
	: public tktk::ComponentBase
{
public:
	
	Sht2D_FlameScript() = default;

public:

	void start();
	void update();

private:

	// 最大のｙ方向スケール
	constexpr static float MaxYScaleRate{ 1.4f };

	// スケーリングタイマーの最大値（秒）
	constexpr static float ScalingMaxTimeSec{ 0.3f };

private:

	// スケーリング用タイマー（秒）
	float									m_scalingSecTimer{ 0.0f };

	tktk::ComponentPtr<tktk::Transform2D>	m_transform;
};
#endif // !SHT_2D_FLAME_SCRIPT_H_