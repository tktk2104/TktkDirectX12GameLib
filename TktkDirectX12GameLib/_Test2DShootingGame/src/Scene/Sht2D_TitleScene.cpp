#include "Sht2D_TitleScene.h"

#include "../GameObject/TitleSceneObjects/TitleSceneLogo/Sht2D_TitleSceneLogo.h"
#include "../GameObject/TitleSceneObjects/TitleSceneMenu/Sht2D_TitleSceneMenu.h"

void Sht2D_TitleScene::start()
{
	Sht2D_TitleSceneLogo::create();
	Sht2D_TitleSceneMenu::create();
}
