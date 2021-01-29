#include "Sht2D_StageSelectScene.h"

#include "../GameObject/StageSelectSceneObjects/StageSelectSceneLogo/Sht2D_StageSelectSceneLogo.h"
#include "../GameObject/StageSelectSceneObjects/StageSelectSceneMenu/Sht2D_StageSelectSceneMenu.h"

void Sht2D_StageSelectScene::start()
{
	// ステージセレクトシーンのロゴオブジェクトを作る
	Sht2D_StageSelectSceneLogo::create();

	// ステージセレクトシーンのメニューオブジェクト
	Sht2D_StageSelectSceneMenu::create();
}
