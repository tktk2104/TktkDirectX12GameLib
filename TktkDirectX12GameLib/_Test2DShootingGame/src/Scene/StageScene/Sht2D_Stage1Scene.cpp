#include "Sht2D_Stage1Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage1Scene::start()
{
	Sht2D_ObjectSpawner::create("res/csv/Stage1.txt");
}
