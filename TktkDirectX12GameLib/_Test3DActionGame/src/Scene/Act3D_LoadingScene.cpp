#include "Act3D_LoadingScene.h"

#include "../Enums/Id/ResourceIds.h"

#include <TktkDX12GameLibInitializer.h>

#include "../GameObject/LightObjects/DefaultLight/Act3D_DefaultLight.h"
#include "../GameObject/StageObjects/BaseGround/Act3D_BaseGround.h"

// メッシュを読み込む
inline void loadMesh(const std::string& filePath, MeshId meshId, SkeletonId skeletonId)
{
	tktk::MeshLoadPmxArgs loadArgs{};
	loadArgs.filePath			= filePath;
	loadArgs.createBasicMeshId	= static_cast<int>(meshId);
	loadArgs.createSkeletonId	= static_cast<int>(skeletonId);

	tktk::DX12GameManager::loadPmx(loadArgs, tktk::MeshDrawFuncRunnerInitParam::create().useBone(true).writeShadowMap(true));
}

// ビルボードを読み込む
inline void loadBillBoard(const std::string& filePath, BillBoardId billBoardId, bool isEffect)
{
	tktk::BillboardMaterialInitParam initParam{};
	initParam.srvBufferType		= tktk::BufferType::texture;
	initParam.useBufferHandle	= tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath);
	initParam.maxInstanceCount	= 256U;
	initParam.isEffect			= isEffect;

	tktk::DX12GameManager::createBillboardMaterialAndAttachId(billBoardId, initParam, tktk::BillboardDrawFuncRunnerInitParam::create());
}

// スプライトを読み込む
inline void loadSprite(const std::string& filePath, SpriteId spriteId)
{
	tktk::SpriteMaterialInitParam initParam{};
	initParam.srvBufferType		= tktk::BufferType::texture;
	initParam.useBufferHandle	= tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath);

	tktk::DX12GameManager::createSpriteMaterialAndAttachId(spriteId, initParam);
}

void Act3D_LoadingScene::start()
{
	// 黒スプライトマテリアルを作る
	tktk::SpriteMaterialInitParam initParam{};
	initParam.srvBufferType		= tktk::BufferType::texture;
	initParam.useBufferHandle	= tktk::DX12GameManager::getSystemHandle(tktk::SystemTextureBufferType::Black4x4);
	tktk::DX12GameManager::createSpriteMaterialAndAttachId(SpriteId::Black4x4, initParam);

	// スプライトを読み込む
	loadSprite("res/image/HpBarFrame.png",				SpriteId::HpBarFrame);
	loadSprite("res/image/HpBarBackGround.png",			SpriteId::HpBarBackGround);
	loadSprite("res/image/PlayerHpBar.png",				SpriteId::PlayerHpBar);
	loadSprite("res/image/PlayerHpUiGuide.png",			SpriteId::PlayerHpBarGuide);
	loadSprite("res/image/TitleSceneBackGround.png",	SpriteId::TitleSceneBackGround);
	loadSprite("res/image/GameClearBackGround.png",		SpriteId::GameClearSceneBackGround);
	loadSprite("res/image/GameOverBackGround.png",		SpriteId::GameOverSceneBackGround);

	// ビルボードを読み込む
	loadBillBoard("res/image/spark.png", BillBoardId::Spark, true);

	// メッシュを読み込む
	loadMesh("res/mesh/player/Paladin.pmx",						MeshId::Player,		SkeletonId::Player);
	loadMesh("res/mesh/fighterEnemy/maw_j_laygo.pmx",			MeshId::FighterEnemy,	SkeletonId::FighterEnemy);
	loadMesh("res/mesh/shooterEnemy/warzombie_f_pedroso.pmx",	MeshId::ShooterEnemy,	SkeletonId::ShooterEnemy);
	loadMesh("res/mesh/bossEnemy/warrok_w_kurniawan.pmx",		MeshId::BossEnemy,		SkeletonId::BossEnemy);

	// スカイボックスメッシュを作る
	tktk::DX12GameManager::makeSkyBoxMeshAndAttachId(
		MeshId::SkyBox,
		tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/image/skyBoxTexture.png"),
		tktk::MeshDrawFuncRunnerInitParam::create()
	);

	// 草ブロックメッシュを作る
	tktk::DX12GameManager::makeBoxMeshAndAttachId(
		MeshId::GrassBlock,
		tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/image/grassBlockTexture.png"),
		tktk::MeshDrawFuncRunnerInitParam::create().writeShadowMap(true)
	);

	// サウンドを読み込む
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::TitleBGM,					"res/bgm/Instavista.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::GamePlayBGM,				"res/bgm/JordenOgHimlen.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::ResultBGM,					"res/bgm/Nikki.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerWalk,				"res/sound/playerWalk.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerRun,					"res/sound/playerRun.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerAttack1,				"res/sound/playerAttack1.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerAttack2,				"res/sound/playerAttack2.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerJumpAttack,			"res/sound/playerJumpAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerDamage,				"res/sound/playerDamage.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::PlayerDead,				"res/sound/playerDead.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::FighterEnemyAttack1,		"res/sound/fighterEnemyAttack1.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::FighterEnemyAttack2,		"res/sound/fighterEnemyAttack2.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::FighterEnemyJumpAttack,	"res/sound/fighterEnemyJumpAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::FighterEnemyDamage,		"res/sound/fighterEnemyDamage.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::FighterEnemyDead,			"res/sound/fighterEnemyDead.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::ShooterEnemyAttack,		"res/sound/shooterEnemyAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::ShooterEnemyShot,			"res/sound/shooterEnemyShot.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::ShooterEnemyDamage,		"res/sound/shooterEnemyDamage.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::ShooterEnemyDead,			"res/sound/shooterEnemyDead.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::BossEnemyNormalAttack,		"res/sound/bossEnemyNormalAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::BossEnemyJumpAttack,		"res/sound/bossEnemyJumpAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::BossEnemyRollAttack,		"res/sound/bossEnemyRollAttack.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::BossEnemyDead,				"res/sound/bossEnemyDead.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::HeavyBlow,					"res/sound/blowHeavy.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::LightBlow,					"res/sound/blowLight.wav");

	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::HeavySword,				"res/sound/swordLight.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::MiddleSword,				"res/sound/swordMiddle.wav");
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::LightSword,				"res/sound/swordHeavy.wav");
	
	tktk::DX12GameManager::loadSoundAndAttachId(SoundId::Confirm,					"res/sound/confirm.wav");

	// モーションを読み込む
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerIdle,			"res/motion/player/playerIdle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkForward,	"res/motion/player/playerWalkForward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkBackward,	"res/motion/player/playerWalkBackward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkLeft,		"res/motion/player/playerWalkLeft.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkRight,		"res/motion/player/playerWalkRight.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerRunForward,	"res/motion/player/playerRunForward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerDodge,			"res/motion/player/playerDodge.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerDamage,		"res/motion/player/playerDamage.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerDead,			"res/motion/player/playerDead.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerAttack1,		"res/motion/player/playerAttack_2.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerAttack2,		"res/motion/player/playerAttack_1.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerJumpAttack,	"res/motion/player/playerJumpAttack.vmd");

	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyIdle,		"res/motion/fighterEnemy/Beta@mutant_idle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyStretchIdle,	"res/motion/fighterEnemy/Beta@mutant_idle_1.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyWalk,		"res/motion/fighterEnemy/Beta@mutant_walking.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyRun,			"res/motion/fighterEnemy/Beta@mutant_run.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyPunch,		"res/motion/fighterEnemy/Beta@mutant_punch.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemySwiping,		"res/motion/fighterEnemy/Beta@mutant_swiping.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyJumpAttack,	"res/motion/fighterEnemy/Beta@mutant_jump_attack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyDamage,		"res/motion/fighterEnemy/Beta@mutant_damage.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyDead,		"res/motion/fighterEnemy/Beta@mutant_dying.vmd");

	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyIdle,		"res/motion/shooterEnemy/shooterEnemyIdle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyWalk,		"res/motion/shooterEnemy/shooterEnemyWalk.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyAttack,		"res/motion/shooterEnemy/shooterEnemyAttack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyShot,		"res/motion/shooterEnemy/shooterEnemyShot.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyDamage,		"res/motion/shooterEnemy/shooterEnemyDamage.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::ShooterEnemyDead,		"res/motion/shooterEnemy/shooterEnemyDead.vmd");

	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyIlde,			"res/motion/bossEnemy/bossEnemyIdle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyRun,			"res/motion/bossEnemy/bossEnemyRun.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyNormalAttack,	"res/motion/bossEnemy/bossEnemyNormalAttack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyJumpAttack,		"res/motion/bossEnemy/bossEnemyJumpAttack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyRoolAttack,		"res/motion/bossEnemy/bossEnemyRollAttack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyDown,			"res/motion/bossEnemy/bossEnemyDown.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyStandUp,		"res/motion/bossEnemy/bossEnemyStandUp.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::BossEnemyDead,			"res/motion/bossEnemy/bossEnemyDead.vmd");

	// デフォルトのライトを作る
	Act3D_DefaultLight::create({ 0.0f, 20.0f, -20.0f });

	// デフォルトの地面を作る
	Act3D_BaseGround::create();

	// 読み込みシーンを無効にする
	tktk::DX12GameManager::disableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));

	// タイトルシーンを有効にする
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Title));
}
