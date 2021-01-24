#ifndef SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_
#define SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_BaseBackGroundSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_BaseBackGroundSpawnerScript() = default;

public:

	void awake();
	void update();

public:

	void endSpawn();

private:

	constexpr static tktkMath::Vector2 FirstSpawnPos	{ 960.0f, -256.0f };

	constexpr static tktkMath::Vector2 VelocityPerSec	{ 0.0f, 512.0f };

private:

	bool m_endSpawn{ false };

	tktk::GameObjectPtr m_beforeCreatedObject;
};
#endif // !SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_