#ifndef SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_
#define SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_StreamingLineSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_StreamingLineSpawnerScript() = default;

public:

	void update();

private:

	constexpr static tktkMath::Vector2	VelocityPerSec					{ 0.0f, 1024.0f };

	constexpr static size_t				SpawnStreamingLineCountPerFrame { 4U };

	constexpr static float				EndSpawnBackGroundTimeSec		{ 30.0f };

private:

	float m_endSpawnBackGroundSecTimer{ 0.0f };

	tktk::GameObjectPtr m_beforeCreatedObject;
};
#endif // !SHT_2D_STREAMING_LINE_SPAWNER_SCRIPT_H_