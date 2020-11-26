#include "Act3D_TitleScene.h"

#include "../GameObject/TitleSceneObjects/TitleBgmPlayer/Act3D_TitleBgmPlayer.h"
#include "../GameObject/TitleSceneObjects/TitleSceneBackGround/Act3D_TitleSceneBackGround.h"
#include "../GameObject/TitleSceneObjects/TitleCamera/Act3D_TitleCamera.h"
#include "../GameObject/TitleSceneObjects/TitleSceneChanger/Act3D_TitleSceneChanger.h"

void Act3D_TitleScene::start()
{
	// �^�C�g���V�[��Bgm�Đ��I�u�W�F�N�g
	Act3D_TitleBgmPlayer::create();

	// �^�C�g���V�[�������w�i�̃I�u�W�F�N�g
	Act3D_TitleSceneBackGround::create();

	// �^�C�g���V�[���̃J�����I�u�W�F�N�g
	Act3D_TitleCamera::create();

	// �^�C�g���V�[������̑J�ڃI�u�W�F�N�g�����
	Act3D_TitleSceneChanger::create();
}