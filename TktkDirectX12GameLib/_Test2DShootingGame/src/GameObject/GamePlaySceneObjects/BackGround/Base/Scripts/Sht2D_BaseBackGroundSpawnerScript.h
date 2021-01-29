#ifndef SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_
#define SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 基地の背景を出現させるコンポーネント
class Sht2D_BaseBackGroundSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_BaseBackGroundSpawnerScript() = default;

public:

	void awake();
	void update();

public:

	// 背景の生成を止める
	void endSpawn();

private:

	// 最初に出現させる基地の背景の座標
	constexpr static tktkMath::Vector2 FirstSpawnPos	{ 960.0f, -256.0f };

	// 基地の背景の毎秒の移動速度
	constexpr static tktkMath::Vector2 VelocityPerSec	{ 0.0f, 512.0f };

private:

	// 背景の生成を止めるフラグ
	bool m_endSpawn{ false };

	// 前回生成した背景オブジェクトポインタ
	tktk::GameObjectPtr m_beforeCreatedObject;
};
#endif // !SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_