#include "Act3D_TitleScene.h"

#include "../GameObject/BgmPlayer/Act3D_TitleBgmPlayer.h"
#include "../GameObject/TitleObjects/TitleSceneBackGround/Act3D_TitleSceneBackGround.h"
#include "../GameObject/TitleObjects/TitleCamera/Act3D_TitleCamera.h"
#include "../GameObject/TitleObjects/TitleSceneChanger/Act3D_TitleSceneChanger.h"

void Act3D_TitleScene::start()
{
	// タイトルBgm再生オブジェクト
	Act3D_TitleBgmPlayer::create();

	// タイトルシーン文字背景のオブジェクト
	Act3D_TitleSceneBackGround::create();

	// タイトルシーンのカメラを作る
	Act3D_TitleCamera::create();

	// タイトルシーンからの遷移オブジェクトを作る
	Act3D_TitleSceneChanger::create();
}

void Act3D_TitleScene::end()
{
}