#include "Act3D_LoadingScene.h"

#include "../Enums/Id/ResourceIds.h"

#include <TktkDX12GameLibInitializer.h>

#include "../GameObject/LightObjects/DefaultLight/Act3D_DefaultLight.h"
#include "../GameObject/StageObjects/BaseGround/Act3D_BaseGround.h"

void Act3D_LoadingScene::start()
{
	// 黒スプライトマテリアルを作る
	tktk::SpriteMaterialInitParam initParam{};
	initParam.srvBufferType		= tktk::BufferType::texture;
	initParam.useBufferHandle	= tktk::DX12GameManager::getSystemHandle(tktk::SystemTextureBufferType::Black4x4);
	tktk::DX12GameManager::createSpriteMaterialAndAttachId(SpriteId::Black4x4, initParam);

	// スプライトを読み込む
	tktk::DX12Game::loadSprite(SpriteId::HpBarFrame,				"res/image/HpBarFrame.png");
	tktk::DX12Game::loadSprite(SpriteId::HpBarBackGround,			"res/image/HpBarBackGround.png");
	tktk::DX12Game::loadSprite(SpriteId::PlayerHpBar,				"res/image/PlayerHpBar.png");
	tktk::DX12Game::loadSprite(SpriteId::PlayerHpBarGuide,			"res/image/PlayerHpUiGuide.png");
	tktk::DX12Game::loadSprite(SpriteId::TitleSceneBackGround,		"res/image/TitleSceneBackGround.png");
	tktk::DX12Game::loadSprite(SpriteId::GameClearSceneBackGround,	"res/image/GameClearBackGround.png");
	tktk::DX12Game::loadSprite(SpriteId::GameOverSceneBackGround,	"res/image/GameOverBackGround.png");

	// ビルボードを読み込む
	tktk::DX12Game::loadBillboard(BillBoardId::Spark, true, "res/image/spark.png");

	// メッシュを読み込む
	tktk::DX12Game::loadMesh(MeshId::Player,		SkeletonId::Player,			true, "res/mesh/player/Paladin.pmx");
	tktk::DX12Game::loadMesh(MeshId::FighterEnemy,	SkeletonId::FighterEnemy,	true, "res/mesh/fighterEnemy/maw_j_laygo.pmx");
	tktk::DX12Game::loadMesh(MeshId::ShooterEnemy,	SkeletonId::ShooterEnemy,	true, "res/mesh/shooterEnemy/warzombie_f_pedroso.pmx");
	tktk::DX12Game::loadMesh(MeshId::BossEnemy,		SkeletonId::ShooterEnemy,	true, "res/mesh/bossEnemy/warrok_w_kurniawan.pmx");

	// スカイボックスメッシュを作る
	tktk::DX12Game::loadSkyBox(MeshId::SkyBox, "res/image/skyBoxTexture.png");

	// 草ブロックメッシュを作る
	tktk::DX12Game::loadBoxMesh(MeshId::GrassBlock, true, "res/image/grassBlockTexture.png");

	// サウンドを読み込む
	tktk::DX12Game::loadSound(SoundId::TitleBGM,				"res/bgm/Instavista.wav");
	tktk::DX12Game::loadSound(SoundId::GamePlayBGM,				"res/bgm/JordenOgHimlen.wav");
	tktk::DX12Game::loadSound(SoundId::ResultBGM,				"res/bgm/Nikki.wav");
	
	tktk::DX12Game::loadSound(SoundId::PlayerWalk,				"res/sound/playerWalk.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerRun,				"res/sound/playerRun.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerAttack1,			"res/sound/playerAttack1.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerAttack2,			"res/sound/playerAttack2.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerJumpAttack,		"res/sound/playerJumpAttack.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerDamage,			"res/sound/playerDamage.wav");
	tktk::DX12Game::loadSound(SoundId::PlayerDead,				"res/sound/playerDead.wav");
	
	tktk::DX12Game::loadSound(SoundId::FighterEnemyAttack1,		"res/sound/fighterEnemyAttack1.wav");
	tktk::DX12Game::loadSound(SoundId::FighterEnemyAttack2,		"res/sound/fighterEnemyAttack2.wav");
	tktk::DX12Game::loadSound(SoundId::FighterEnemyJumpAttack,	"res/sound/fighterEnemyJumpAttack.wav");
	tktk::DX12Game::loadSound(SoundId::FighterEnemyDamage,		"res/sound/fighterEnemyDamage.wav");
	tktk::DX12Game::loadSound(SoundId::FighterEnemyDead,		"res/sound/fighterEnemyDead.wav");
	
	tktk::DX12Game::loadSound(SoundId::ShooterEnemyAttack,		"res/sound/shooterEnemyAttack.wav");
	tktk::DX12Game::loadSound(SoundId::ShooterEnemyShot,		"res/sound/shooterEnemyShot.wav");
	tktk::DX12Game::loadSound(SoundId::ShooterEnemyDamage,		"res/sound/shooterEnemyDamage.wav");
	tktk::DX12Game::loadSound(SoundId::ShooterEnemyDead,		"res/sound/shooterEnemyDead.wav");
	
	tktk::DX12Game::loadSound(SoundId::BossEnemyNormalAttack,	"res/sound/bossEnemyNormalAttack.wav");
	tktk::DX12Game::loadSound(SoundId::BossEnemyJumpAttack,		"res/sound/bossEnemyJumpAttack.wav");
	tktk::DX12Game::loadSound(SoundId::BossEnemyRollAttack,		"res/sound/bossEnemyRollAttack.wav");
	tktk::DX12Game::loadSound(SoundId::BossEnemyDead,			"res/sound/bossEnemyDead.wav");
	
	tktk::DX12Game::loadSound(SoundId::HeavyBlow,				"res/sound/blowHeavy.wav");
	tktk::DX12Game::loadSound(SoundId::LightBlow,				"res/sound/blowLight.wav");

	tktk::DX12Game::loadSound(SoundId::HeavySword,				"res/sound/swordLight.wav");
	tktk::DX12Game::loadSound(SoundId::MiddleSword,				"res/sound/swordMiddle.wav");
	tktk::DX12Game::loadSound(SoundId::LightSword,				"res/sound/swordHeavy.wav");
	
	tktk::DX12Game::loadSound(SoundId::Confirm,					"res/sound/confirm.wav");

	// モーションを読み込む
	tktk::DX12Game::loadMotion(MotionId::PlayerIdle,			"res/motion/player/playerIdle.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerWalkForward,	"res/motion/player/playerWalkForward.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerWalkBackward,	"res/motion/player/playerWalkBackward.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerWalkLeft,		"res/motion/player/playerWalkLeft.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerWalkRight,		"res/motion/player/playerWalkRight.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerRunForward,	"res/motion/player/playerRunForward.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerDodge,			"res/motion/player/playerDodge.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerDamage,		"res/motion/player/playerDamage.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerDead,			"res/motion/player/playerDead.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerAttack1,		"res/motion/player/playerAttack_2.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerAttack2,		"res/motion/player/playerAttack_1.vmd");
	tktk::DX12Game::loadMotion(MotionId::PlayerJumpAttack,	"res/motion/player/playerJumpAttack.vmd");

	tktk::DX12Game::loadMotion(MotionId::FighterEnemyIdle,		"res/motion/fighterEnemy/Beta@mutant_idle.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyStretchIdle,	"res/motion/fighterEnemy/Beta@mutant_idle_1.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyWalk,		"res/motion/fighterEnemy/Beta@mutant_walking.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyRun,			"res/motion/fighterEnemy/Beta@mutant_run.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyPunch,		"res/motion/fighterEnemy/Beta@mutant_punch.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemySwiping,		"res/motion/fighterEnemy/Beta@mutant_swiping.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyJumpAttack,	"res/motion/fighterEnemy/Beta@mutant_jump_attack.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyDamage,		"res/motion/fighterEnemy/Beta@mutant_damage.vmd");
	tktk::DX12Game::loadMotion(MotionId::FighterEnemyDead,		"res/motion/fighterEnemy/Beta@mutant_dying.vmd");

	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyIdle,		"res/motion/shooterEnemy/shooterEnemyIdle.vmd");
	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyWalk,		"res/motion/shooterEnemy/shooterEnemyWalk.vmd");
	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyAttack,		"res/motion/shooterEnemy/shooterEnemyAttack.vmd");
	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyShot,		"res/motion/shooterEnemy/shooterEnemyShot.vmd");
	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyDamage,		"res/motion/shooterEnemy/shooterEnemyDamage.vmd");
	tktk::DX12Game::loadMotion(MotionId::ShooterEnemyDead,		"res/motion/shooterEnemy/shooterEnemyDead.vmd");

	tktk::DX12Game::loadMotion(MotionId::BossEnemyIlde,			"res/motion/bossEnemy/bossEnemyIdle.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyRun,			"res/motion/bossEnemy/bossEnemyRun.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyNormalAttack,	"res/motion/bossEnemy/bossEnemyNormalAttack.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyJumpAttack,		"res/motion/bossEnemy/bossEnemyJumpAttack.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyRoolAttack,		"res/motion/bossEnemy/bossEnemyRollAttack.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyDown,			"res/motion/bossEnemy/bossEnemyDown.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyStandUp,		"res/motion/bossEnemy/bossEnemyStandUp.vmd");
	tktk::DX12Game::loadMotion(MotionId::BossEnemyDead,			"res/motion/bossEnemy/bossEnemyDead.vmd");

	// デフォルトのライトを作る
	Act3D_DefaultLight::create({ 0.0f, 20.0f, -20.0f });

	// デフォルトの地面を作る
	Act3D_BaseGround::create();

	// 読み込みシーンを無効にする
	tktk::DX12Game::disableScene(SceneId::Loading);

	// タイトルシーンを有効にする
	tktk::DX12Game::enableScene(SceneId::Title);
}
