#include "Act3D_TitleScene.h"

#include "../GameObject/TitleSceneObjects/TitleBgmPlayer/Act3D_TitleBgmPlayer.h"
#include "../GameObject/TitleSceneObjects/TitleSceneBackGround/Act3D_TitleSceneBackGround.h"
#include "../GameObject/TitleSceneObjects/TitleCamera/Act3D_TitleCamera.h"
#include "../GameObject/TitleSceneObjects/TitleSceneChanger/Act3D_TitleSceneChanger.h"

void Act3D_TitleScene::start()
{
	// タイトルシーンBgm再生オブジェクト
	Act3D_TitleBgmPlayer::create();

	// タイトルシーン文字背景のオブジェクト
	Act3D_TitleSceneBackGround::create();

	// タイトルシーンのカメラオブジェクト
	Act3D_TitleCamera::create();

	// タイトルシーンからの遷移オブジェクトを作る
	Act3D_TitleSceneChanger::create();
}