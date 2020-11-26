#include "Act3D_ResultScene.h"

#include "../GameObject/ResultSceneObjects/ResultBgmPlayer/Act3D_ResultBgmPlayer.h"
#include "../GameObject/ResultSceneObjects/ResultSceneBackGround/Act3D_ResultSceneBackGround.h"
#include "../GameObject/ResultSceneObjects/ResultCamera/Act3D_ResultCamera.h"
#include "../GameObject/ResultSceneObjects/ResultSceneChanger/Act3D_ResultSceneChanger.h"

void Act3D_ResultScene::start()
{
	// ���U���g�V�[��Bgm�Đ��I�u�W�F�N�g
	Act3D_ResultBgmPlayer::create();

	// ���U���g�V�[�������w�i�̃I�u�W�F�N�g
	Act3D_ResultSceneBackGround::create();

	// ���U���g�V�[���̃J�����I�u�W�F�N�g
	Act3D_ResultCamera::create();

	// ���U���g�V�[������̑J�ڃI�u�W�F�N�g
	Act3D_ResultSceneChanger::create();
}