#include "Sht2D_Stage2Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage2Scene::start()
{
	// �X�e�[�W�Q�̏��ŃG�l�~�[�o���I�u�W�F�N�g�����
	Sht2D_ObjectSpawner::create("res/csv/Stage2.txt");
}
