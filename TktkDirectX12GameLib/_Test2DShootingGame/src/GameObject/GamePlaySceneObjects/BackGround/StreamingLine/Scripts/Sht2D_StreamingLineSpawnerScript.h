#ifndef SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_
#define SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 流れる線を出現させるコンポーネント
class Sht2D_StreamingLineSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_StreamingLineSpawnerScript() = default;

public:

	void update();

private:

	// 流れる線の毎秒の移動速度
	constexpr static tktkMath::Vector2	VelocityPerSec					{ 0.0f, 1024.0f };

	// １フレームで出現する流れる線の数（毎秒の数ではないので注意）
	constexpr static size_t				SpawnStreamingLineCountPerFrame { 4U };
};
#endif // !SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_