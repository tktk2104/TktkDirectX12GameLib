#include "Sht2D_BaseBackGroundSpawnStopperScript.h"

#include "../../../../../Enums/Enums.h"
#include "Sht2D_BaseBackGroundSpawnerScript.h"

void Sht2D_BaseBackGroundSpawnStopperScript::start()
{
	// 基地の背景オブジェクトスポナーオブジェクトを取得する
	tktk::GameObjectPtr baseBackGroundSpawner = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::BaseBackGroundSpawner);

	// 基地の背景オブジェクトスポナーオブジェクトが取得できたら
	if (!baseBackGroundSpawner.expired())
	{
		// 基地の背景を出現させるコンポーネントを取得する
		tktk::ComponentPtr<Sht2D_BaseBackGroundSpawnerScript> baseBackGroundSpawnerScript = baseBackGroundSpawner->getComponent<Sht2D_BaseBackGroundSpawnerScript>();

		// 基地の背景の出現を止める
		baseBackGroundSpawnerScript->endSpawn();
	}

	// 自身のオブジェクトを削除する
	getGameObject()->destroy();
}
