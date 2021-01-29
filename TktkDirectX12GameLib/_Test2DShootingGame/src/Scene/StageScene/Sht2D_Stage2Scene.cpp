#include "Sht2D_Stage2Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage2Scene::start()
{
	// ステージ２の情報でエネミー出現オブジェクトを作る
	Sht2D_ObjectSpawner::create("res/csv/Stage2.txt");
}
