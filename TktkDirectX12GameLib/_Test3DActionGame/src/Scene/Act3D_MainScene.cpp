#include "Act3D_MainScene.h"

#include "../GameObject/BgmPlayer/Act3D_GamePlayBgmPlayer.h"
#include "../GameObject/GameRule/Act3D_GameRule.h"
#include "../GameObject/Ui/PlayerHpBar/Act3D_PlayerHpBar.h"

#include "../GameObject/PlayerObjects/Player/Act3D_Player.h"
#include "../GameObject/EnemyObjects/FighterEnemy/Act3D_FighterEnemy.h"
#include "../GameObject/EnemyObjects/ShooterEnemy/Act3D_ShooterEnemy.h"
#include "../GameObject/EnemyObjects/BossEnemy/Act3D_BossEnemy.h"

#include "../GameObject/StageObjects/GrassBlock/Act3D_GrassBlock.h"

#include "../GameObject/_DebugObjects/DebugSprite/Act3D_DebugSprite.h"

void Act3D_MainScene::start()
{
	// ゲームプレイBgm再生オブジェクト
	Act3D_GamePlayBgmPlayer::create();

	// ゲームルールオブジェクト
	Act3D_GameRule::create();

	// プレイヤーを作る
	Act3D_Player::create({ 0.0f, 0.0f, -10.0f }, tktkMath::Vector3_v::zero);

	// プレイヤーHP UI
	Act3D_PlayerHpBar::create({ 100.0f, 50.0f });
}

void Act3D_MainScene::end()
{
}
