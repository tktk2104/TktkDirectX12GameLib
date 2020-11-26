#include "Act3D_TitleScene.h"

#include "../GameObject/BgmPlayer/Act3D_TitleBgmPlayer.h"
#include "../GameObject/TitleObjects/TitleSceneBackGround/Act3D_TitleSceneBackGround.h"
#include "../GameObject/TitleObjects/TitleCamera/Act3D_TitleCamera.h"
#include "../GameObject/TitleObjects/TitleSceneChanger/Act3D_TitleSceneChanger.h"

void Act3D_TitleScene::start()
{
	// �^�C�g��Bgm�Đ��I�u�W�F�N�g
	Act3D_TitleBgmPlayer::create();

	// �^�C�g���V�[�������w�i�̃I�u�W�F�N�g
	Act3D_TitleSceneBackGround::create();

	// �^�C�g���V�[���̃J���������
	Act3D_TitleCamera::create();

	// �^�C�g���V�[������̑J�ڃI�u�W�F�N�g�����
	Act3D_TitleSceneChanger::create();
}

void Act3D_TitleScene::end()
{
}