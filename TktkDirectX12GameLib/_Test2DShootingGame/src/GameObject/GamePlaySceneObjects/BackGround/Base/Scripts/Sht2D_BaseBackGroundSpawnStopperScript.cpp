#include "Sht2D_BaseBackGroundSpawnStopperScript.h"

#include "../../../../../Enums/Enums.h"
#include "Sht2D_BaseBackGroundSpawnerScript.h"

void Sht2D_BaseBackGroundSpawnStopperScript::start()
{
	auto baseBackGroundSpawner = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::BaseBackGroundSpawner);

	if (!baseBackGroundSpawner.expired())
	{
		auto baseBackGroundSpawnerScript = baseBackGroundSpawner->getComponent<Sht2D_BaseBackGroundSpawnerScript>();

		baseBackGroundSpawnerScript->endSpawn();
	}

	getGameObject()->destroy();
}
