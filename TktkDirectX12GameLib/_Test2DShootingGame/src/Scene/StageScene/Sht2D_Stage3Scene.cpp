#include "Sht2D_Stage3Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage3Scene::start()
{
	Sht2D_ObjectSpawner::create("res/csv/Stage3.txt");
}
