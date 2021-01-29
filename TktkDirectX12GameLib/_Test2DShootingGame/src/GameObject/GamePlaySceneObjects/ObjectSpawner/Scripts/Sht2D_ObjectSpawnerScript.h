#ifndef SHT_2D_OBJECT_SPAWNER_SCRIPT_H_
#define SHT_2D_OBJECT_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// 時間経過でオブジェクトを出現させるコンポーネント
class Sht2D_ObjectSpawnerScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_ObjectSpawnerScript(const std::string& csvFilePath);

public:

	void update();

private:

	// 出現させるオブジェクトの種類
	enum class SpawnObjectType
	{
		StreamingLine,
		BaseBackGround,
		BaseBackGroundStopper,
		TankEnemy,
		SpreadBulletEnemy,
	};

private:

	// 出現させるオブジェクトの情報
	struct SpawnObjectData
	{
		// 出現時間（秒）
		float				spawnTimeSec{};

		// 出現するオブジェクトの種類
		SpawnObjectType		objectType{};

		// 出現座標
		tktkMath::Vector2	spawnPos{};

		// 出現時回転（度数法）
		float				spawnRotateDeg{};
	};

private:

	// 現在の経過時間
	float m_curTime{ 0.0f };

	// 現在の総出現数
	size_t m_curSpawnObjectCount{ 0U };

	// 出現データの配列
	std::vector<std::unique_ptr<SpawnObjectData>> m_spawnObjectDataArray;
};
#endif // !SHT_2D_OBJECT_SPAWNER_SCRIPT_H_