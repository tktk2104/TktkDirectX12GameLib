#include "Sht2D_Stage3Scene.h"

#include "../../GameObject/GamePlaySceneObjects/ObjectSpawner/Sht2D_ObjectSpawner.h"

void Sht2D_Stage3Scene::start()
{
	// �X�e�[�W�R�̏��ŃG�l�~�[�o���I�u�W�F�N�g�����
	Sht2D_ObjectSpawner::create("res/csv/Stage3.txt");
}
