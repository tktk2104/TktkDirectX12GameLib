#ifndef SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_
#define SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_

#include <TktkDX12GameLib.h>

// ��n�̔w�i���o��������R���|�[�l���g
class Sht2D_BaseBackGroundSpawnerScript
	: public tktk::ComponentBase
{
public:

	Sht2D_BaseBackGroundSpawnerScript() = default;

public:

	void awake();
	void update();

public:

	// �w�i�̐������~�߂�
	void endSpawn();

private:

	// �ŏ��ɏo���������n�̔w�i�̍��W
	constexpr static tktkMath::Vector2 FirstSpawnPos	{ 960.0f, -256.0f };

	// ��n�̔w�i�̖��b�̈ړ����x
	constexpr static tktkMath::Vector2 VelocityPerSec	{ 0.0f, 512.0f };

private:

	// �w�i�̐������~�߂�t���O
	bool m_endSpawn{ false };

	// �O�񐶐������w�i�I�u�W�F�N�g�|�C���^
	tktk::GameObjectPtr m_beforeCreatedObject;
};
#endif // !SHT_2D_BASE_BACK_GROUND_SPAWNER_SCRIPT_H_