#include "Act3D_MainScene.h"

#include "../GameObject/MainSceneObjects/GamePlayBgmPlayer/Act3D_GamePlayBgmPlayer.h"
#include "../GameObject/MainSceneObjects/GameRule/Act3D_GameRule.h"
#include "../GameObject/Ui/PlayerHpBar/Act3D_PlayerHpBar.h"
#include "../GameObject/MainSceneObjects/PlayerObjects/Player/Act3D_Player.h"

void Act3D_MainScene::start()
{
	// �Q�[���v���CBgm�Đ��I�u�W�F�N�g
	Act3D_GamePlayBgmPlayer::create();

	// �Q�[�����[���I�u�W�F�N�g
	Act3D_GameRule::create();

	// �v���C���[�I�u�W�F�N�g
	Act3D_Player::create({ 0.0f, 0.0f, -10.0f }, tktkMath::Vector3_v::zero);

	// �v���C���[HP UI�I�u�W�F�N�g
	Act3D_PlayerHpBar::create({ 100.0f, 50.0f });
}