#include "Sht2D_ResultScene.h"

#include "../GameObject/ResultSceneObjects/ResultSceneLogo/Sht2D_ResultSceneLogo.h"
#include "../GameObject/ResultSceneObjects/ResultSceneMenu/Sht2D_ResultSceneMenu.h"

void Sht2D_ResultScene::start()
{
	// リザルトシーンのロゴオブジェクトを作る
	Sht2D_ResultSceneLogo::create();

	// リザルトシーンのメニューオブジェクト
	Sht2D_ResultSceneMenu::create();
}
