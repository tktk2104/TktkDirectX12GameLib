#include "Sht2D_StageSelectScene.h"

#include "../GameObject/StageSelectSceneObjects/StageSelectSceneLogo/Sht2D_StageSelectSceneLogo.h"
#include "../GameObject/StageSelectSceneObjects/StageSelectSceneMenu/Sht2D_StageSelectSceneMenu.h"

void Sht2D_StageSelectScene::start()
{
	Sht2D_StageSelectSceneLogo::create();
	Sht2D_StageSelectSceneMenu::create();
}
