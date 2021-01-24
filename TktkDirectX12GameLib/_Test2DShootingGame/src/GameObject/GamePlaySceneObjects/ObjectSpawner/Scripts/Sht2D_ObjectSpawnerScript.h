#ifndef SHT_2D_OBJECT_SPAWNER_SCRIPT_H_
#define SHT_2D_OBJECT_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_ObjectSpawnerScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_ObjectSpawnerScript(const std::string& csvFilePath);

public:

	void update();

private:

	enum class SpawnObjectType
	{
		StreamingLine,
		BaseBackGround,
		BaseBackGroundStopper,
		TankEnemy,
		SpreadBulletEnemy,
	};

private:

	struct SpawnObjectData
	{
		float				spawnTime;

		SpawnObjectType		objectType;

		tktkMath::Vector2	spawnPos;

		float				spawnRotate;
	};

private:

	float m_curTime{ 0.0f };

	size_t m_curSpawnObjectCount{ 0U };

	std::vector<std::unique_ptr<SpawnObjectData>> m_spawnObjectDataArray;
};
#endif // !SHT_2D_OBJECT_SPAWNER_SCRIPT_H_