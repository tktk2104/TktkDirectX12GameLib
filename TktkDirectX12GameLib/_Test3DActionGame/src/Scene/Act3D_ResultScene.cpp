#include "Act3D_ResultScene.h"

#include "../GameObject/BgmPlayer/Act3D_ResultBgmPlayer.h"
#include "../GameObject/ResultSceneObjects/ResultSceneBackGround/Act3D_ResultSceneBackGround.h"
#include "../GameObject/ResultSceneObjects/ResultCamera/Act3D_ResultCamera.h"
#include "../GameObject/ResultSceneObjects/ResultSceneChanger/Act3D_ResultSceneChanger.h"

void Act3D_ResultScene::start()
{
	Act3D_ResultBgmPlayer::create();
	Act3D_ResultSceneBackGround::create();
	Act3D_ResultCamera::create();
	Act3D_ResultSceneChanger::create();
}
