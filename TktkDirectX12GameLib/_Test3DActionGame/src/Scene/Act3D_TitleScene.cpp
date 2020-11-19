#include "Act3D_TitleScene.h"

#include "../GameObject/LightObjects/DefaultLight/Act3D_DefaultLight.h"
#include "../GameObject/StageObjects/BaseGround/Act3D_BaseGround.h"

#include "../GameObject/PlayerObjects/Player/Act3D_Player.h"
#include "../GameObject/EnemyObjects/FighterEnemy/Act3D_FighterEnemy.h"
#include "../GameObject/EnemyObjects/ShooterEnemy/Act3D_ShooterEnemy.h"
#include "../GameObject/EnemyObjects/BossEnemy/Act3D_BossEnemy.h"

#include "../GameObject/StageObjects/GrassBlock/Act3D_GrassBlock.h"

#include "../GameObject/_DebugObjects/DebugCamera/Act3D_DebugCamera.h"
#include "../GameObject/_DebugObjects/DebugSprite/Act3D_DebugSprite.h"

void Act3D_TitleScene::start()
{
	// デフォルトのライトを作る
	Act3D_DefaultLight::create({ 0.0f, 20.0f, -20.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -20.0f, 20.0f }));

	// デフォルトの地面を作る
	Act3D_BaseGround::create();

	// プレイヤーを作る
	Act3D_Player::create({ 0.0f, 3.0f, 0.0f }, tktkMath::Vector3_v::zero);

	//Act3D_FighterEnemy::create({ 10.0f, 3.0f, 10.0f }, tktkMath::Vector3_v::zero);

	Act3D_ShooterEnemy::create({ 0.0f, 3.0f, 10.0f }, tktkMath::Vector3_v::zero);

	//Act3D_BossEnemy::create({ -10.0f, 3.0f, 10.0f }, tktkMath::Vector3_v::zero);

	//Act3D_GrassBlock::create({ 0.0f, 1.0f, 1.0f });

	// デバック用カメラ
	//Act3D_DebugCamera::create({ 0.0f, 3.0f, 0.0f });

	//Act3D_DebugSprite::create(tktk::DX12Game::getWindowSize());
}

void Act3D_TitleScene::end()
{
}