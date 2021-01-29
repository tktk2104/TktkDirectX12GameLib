#include "Sht2D_Stage3Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage3Scene::start()
{
	// ステージ３の情報でエネミー出現オブジェクトを作る
	Sht2D_ObjectSpawner::create("res/csv/Stage3.txt");
}
