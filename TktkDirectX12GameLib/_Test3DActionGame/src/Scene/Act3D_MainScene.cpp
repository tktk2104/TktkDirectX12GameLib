#include "Act3D_MainScene.h"

#include "../GameObject/MainSceneObjects/GamePlayBgmPlayer/Act3D_GamePlayBgmPlayer.h"
#include "../GameObject/MainSceneObjects/GameRule/Act3D_GameRule.h"
#include "../GameObject/Ui/PlayerHpBar/Act3D_PlayerHpBar.h"
#include "../GameObject/MainSceneObjects/PlayerObjects/Player/Act3D_Player.h"

void Act3D_MainScene::start()
{
	// ゲームプレイBgm再生オブジェクト
	Act3D_GamePlayBgmPlayer::create();

	// ゲームルールオブジェクト
	Act3D_GameRule::create();

	// プレイヤーオブジェクト
	Act3D_Player::create({ 0.0f, 0.0f, -10.0f }, tktkMath::Vector3_v::zero);

	// プレイヤーHP UIオブジェクト
	Act3D_PlayerHpBar::create({ 100.0f, 50.0f });
}