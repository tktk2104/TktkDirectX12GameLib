#include "Sht2D_BaseBackGroundSpawnStopperScript.h"

#include "../../../../../Enums/Enums.h"
#include "Sht2D_BaseBackGroundSpawnerScript.h"

void Sht2D_BaseBackGroundSpawnStopperScript::start()
{
	// ��n�̔w�i�I�u�W�F�N�g�X�|�i�[�I�u�W�F�N�g���擾����
	tktk::GameObjectPtr baseBackGroundSpawner = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::BaseBackGroundSpawner);

	// ��n�̔w�i�I�u�W�F�N�g�X�|�i�[�I�u�W�F�N�g���擾�ł�����
	if (!baseBackGroundSpawner.expired())
	{
		// ��n�̔w�i���o��������R���|�[�l���g���擾����
		tktk::ComponentPtr<Sht2D_BaseBackGroundSpawnerScript> baseBackGroundSpawnerScript = baseBackGroundSpawner->getComponent<Sht2D_BaseBackGroundSpawnerScript>();

		// ��n�̔w�i�̏o�����~�߂�
		baseBackGroundSpawnerScript->endSpawn();
	}

	// ���g�̃I�u�W�F�N�g���폜����
	getGameObject()->destroy();
}
