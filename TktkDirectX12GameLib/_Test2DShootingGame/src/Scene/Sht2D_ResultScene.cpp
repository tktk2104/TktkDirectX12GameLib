#include "Sht2D_ResultScene.h"

#include "../GameObject/ResultSceneObjects/ResultSceneLogo/Sht2D_ResultSceneLogo.h"
#include "../GameObject/ResultSceneObjects/ResultSceneMenu/Sht2D_ResultSceneMenu.h"

void Sht2D_ResultScene::start()
{
	Sht2D_ResultSceneLogo::create();
	Sht2D_ResultSceneMenu::create();
}
