#ifndef SHT_2D_OBJECT_SPAWNER_SCRIPT_H_
#define SHT_2D_OBJECT_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ���Ԍo�߂ŃI�u�W�F�N�g���o��������R���|�[�l���g
class Sht2D_ObjectSpawnerScript
	: public tktk::ComponentBase
{
public:

	explicit Sht2D_ObjectSpawnerScript(const std::string& csvFilePath);

public:

	void update();

private:

	// �o��������I�u�W�F�N�g�̎��
	enum class SpawnObjectType
	{
		StreamingLine,
		BaseBackGround,
		BaseBackGroundStopper,
		TankEnemy,
		SpreadBulletEnemy,
	};

private:

	// �o��������I�u�W�F�N�g�̏��
	struct SpawnObjectData
	{
		// �o�����ԁi�b�j
		float				spawnTimeSec{};

		// �o������I�u�W�F�N�g�̎��
		SpawnObjectType		objectType{};

		// �o�����W
		tktkMath::Vector2	spawnPos{};

		// �o������]�i�x���@�j
		float				spawnRotateDeg{};
	};

private:

	// ���݂̌o�ߎ���
	float m_curTime{ 0.0f };

	// ���݂̑��o����
	size_t m_curSpawnObjectCount{ 0U };

	// �o���f�[�^�̔z��
	std::vector<std::unique_ptr<SpawnObjectData>> m_spawnObjectDataArray;
};
#endif // !SHT_2D_OBJECT_SPAWNER_SCRIPT_H_