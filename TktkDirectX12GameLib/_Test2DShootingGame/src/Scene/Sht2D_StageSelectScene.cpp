#include "Sht2D_StageSelectScene.h"

#include "../GameObject/StageSelectSceneObjects/StageSelectSceneLogo/Sht2D_StageSelectSceneLogo.h"
#include "../GameObject/StageSelectSceneObjects/StageSelectSceneMenu/Sht2D_StageSelectSceneMenu.h"

void Sht2D_StageSelectScene::start()
{
	// �X�e�[�W�Z���N�g�V�[���̃��S�I�u�W�F�N�g�����
	Sht2D_StageSelectSceneLogo::create();

	// �X�e�[�W�Z���N�g�V�[���̃��j���[�I�u�W�F�N�g
	Sht2D_StageSelectSceneMenu::create();
}
