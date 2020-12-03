#include "Act3D_ResultScene.h"

#include "../GameObject/ResultSceneObjects/ResultBgmPlayer/Act3D_ResultBgmPlayer.h"
#include "../GameObject/ResultSceneObjects/ResultSceneBackGround/Act3D_ResultSceneBackGround.h"
#include "../GameObject/ResultSceneObjects/ResultCamera/Act3D_ResultCamera.h"
#include "../GameObject/ResultSceneObjects/ResultSceneChanger/Act3D_ResultSceneChanger.h"

void Act3D_ResultScene::start()
{
	// リザルトシーンBgm再生オブジェクト
	Act3D_ResultBgmPlayer::create();

	// リザルトシーン文字背景のオブジェクト
	Act3D_ResultSceneBackGround::create();

	// リザルトシーンのカメラオブジェクト
	Act3D_ResultCamera::create();

	// リザルトシーンからの遷移オブジェクト
	Act3D_ResultSceneChanger::create();
}