#include "Act3D_LoadingScene.h"

#include "../Enums/Id/ResourceIds.h"

#include <TktkDX12GameLibInitializer.h>

inline void loadMesh(const std::string& filePath, BasicMeshId meshId, SkeletonId skeletonId)
{
	tktk::MeshLoadPmxArgs loadArgs{};
	loadArgs.filePath			= filePath;
	loadArgs.createBasicMeshId	= static_cast<int>(meshId);
	loadArgs.createSkeletonId	= static_cast<int>(skeletonId);

	tktk::DX12GameManager::loadPmx(loadArgs, tktk::MeshDrawFuncRunnerInitParam::create().useBone(true).writeShadowMap(true));
}

inline void loadBillBoard(const std::string& filePath, BillBoardId billBoardId)
{
	tktk::BillboardMaterialInitParam initParam{};
	initParam.srvBufferType		= tktk::BufferType::texture;
	initParam.useBufferHandle	= tktk::DX12GameManager::cpuPriorityLoadTextureBuffer(filePath);
	initParam.maxInstanceCount	= 256U;

	tktk::DX12GameManager::createBillboardMaterialAndAttachId(billBoardId, initParam, tktk::BillboardDrawFuncRunnerInitParam::create());
}

void Act3D_LoadingScene::start()
{
	auto handle = tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/image/skyBoxTexture.png");
	tktk::SpriteMaterialInitParam initParam{};
	//initParam.srvBufferType				= tktk::BufferType::texture;
	//initParam.useBufferHandle			= handle;
	initParam.srvBufferType			= tktk::BufferType::depthStencil;
	initParam.useBufferHandle		= tktk::DX12GameManager::getSystemHandle(tktk::SystemDsBufferType::ShadowMap);
	tktk::DX12GameManager::createSpriteMaterialAndAttachId(7, initParam);

	// ビルボードを読み込む
	loadBillBoard("res/image/spark.png", BillBoardId::Spark);

	// メッシュを読み込む
	loadMesh("res/mesh/player/Paladin.pmx",						BasicMeshId::Player,		SkeletonId::Player);
	loadMesh("res/mesh/fighterEnemy/maw_j_laygo.pmx",			BasicMeshId::FighterEnemy,	SkeletonId::FighterEnemy);
	loadMesh("res/mesh/shooterEnemy/warzombie_f_pedroso.pmx",	BasicMeshId::ShooterEnemy,	SkeletonId::ShooterEnemy);
	loadMesh("res/mesh/bossEnemy/warrok_w_kurniawan.pmx",		BasicMeshId::BossEnemy,		SkeletonId::BossEnemy);

	// スカイボックスメッシュを作る
	tktk::DX12GameManager::makeSkyBoxMeshAndAttachId(
		BasicMeshId::SkyBox,
		tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/image/skyBoxTexture.png"),
		tktk::MeshDrawFuncRunnerInitParam::create()
	);

	// 草ブロックメッシュを作る
	tktk::DX12GameManager::makeBoxMeshAndAttachId(
		BasicMeshId::GrassBlock,
		tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/image/grassBlockTexture.png"),
		tktk::MeshDrawFuncRunnerInitParam::create().writeShadowMap(true)
	);

	// モーションを読み込む
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerIdle,			"res/motion/player/playerIdle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkForward,	"res/motion/player/playerWalkForward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkBackward,	"res/motion/player/playerWalkBackward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkLeft,		"res/motion/player/playerWalkLeft.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerWalkRight,		"res/motion/player/playerWalkRight.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerRunForward,	"res/motion/player/playerRunForward.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerDamage,		"res/motion/player/playerDamage.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerDead,			"res/motion/player/playerDead.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerAttack1,		"res/motion/player/playerAttack_2.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerAttack2,		"res/motion/player/playerAttack_1.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::PlayerJumpAttack,	"res/motion/player/playerJumpAttack.vmd");

	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyIdle,		"res/motion/mutant/Beta@mutant_idle.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyStretchIdle,	"res/motion/mutant/Beta@mutant_idle_1.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyWalk,		"res/motion/mutant/Beta@mutant_walking.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyRun,			"res/motion/mutant/Beta@mutant_run.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyPunch,		"res/motion/mutant/Beta@mutant_punch.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemySwiping,		"res/motion/mutant/Beta@mutant_swiping.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyJumpAttack,	"res/motion/mutant/Beta@mutant_jump_attack.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyDamage,		"res/motion/mutant/Beta@mutant_damage.vmd");
	tktk::DX12GameManager::loadMotionAndAttachId(MotionId::FighterEnemyDead,		"res/motion/mutant/Beta@mutant_dying.vmd");

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

	// 読み込みシーンを無効にする
	tktk::DX12GameManager::disableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));

	// タイトルシーンを有効にする
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Title));
}
