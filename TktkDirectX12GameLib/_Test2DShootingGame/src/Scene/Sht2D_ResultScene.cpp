#include "Sht2D_ResultScene.h"

#include "../GameObject/ResultSceneObjects/ResultSceneLogo/Sht2D_ResultSceneLogo.h"
#include "../GameObject/ResultSceneObjects/ResultSceneMenu/Sht2D_ResultSceneMenu.h"

void Sht2D_ResultScene::start()
{
	// ���U���g�V�[���̃��S�I�u�W�F�N�g�����
	Sht2D_ResultSceneLogo::create();

	// ���U���g�V�[���̃��j���[�I�u�W�F�N�g
	Sht2D_ResultSceneMenu::create();
}
