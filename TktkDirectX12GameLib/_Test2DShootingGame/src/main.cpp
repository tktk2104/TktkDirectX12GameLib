#include <TktkDX12GameLibDefinition.h>

#include <Windows.h>
#undef min
#undef max

#include <TktkDX12GameLibInitializer.h>

#include "Scene/Sht2D_LoadingScene.h"
#include "Scene/Sht2D_TitleScene.h"
#include "Scene/Sht2D_StageSelectScene.h"
#include "Scene/Sht2D_GamePlayScene.h"
#include "Scene/Sht2D_ResultScene.h"
#include "Scene/StageScene/Sht2D_Stage1Scene.h"
#include "Scene/StageScene/Sht2D_Stage2Scene.h"
#include "Scene/StageScene/Sht2D_Stage3Scene.h"

#include "Enums/Enums.h"

// 「DX12GameManager」の初期設定をする
inline void setUpDX12GameManager(HINSTANCE hInstance, int nCmdShow)
{
	tktk::DX12GameManagerInitParam initParam{};

	// ゲームウィンドウの設定
	initParam.windowParam.hInstance		= hInstance;
	initParam.windowParam.nCmdShow		= nCmdShow;
	initParam.windowParam.windowName	= "Test3DActionGame";
	initParam.windowParam.fullScreen	= false;
	initParam.windowParam.windowSize	= { 1920.0f, 1080.0f };

	// デバックレイヤーを無効にする
	initParam.createDebugLayer = false;

	// DX12GameManagerのセットアップ
	tktk::DX12GameManager::initialize(initParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// 「DX12GameManager」の初期設定をする
	setUpDX12GameManager(hInstance, nCmdShow);

	// 各入力と入力コマンドを結びつける
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Return);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::KeybordKeyType::key_M);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::GamePadBtnType::btn_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::KeybordKeyType::key_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::GamePadBtnType::btn_X);

	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveUp,	tktk::KeybordKeyType::key_W);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveDown,	tktk::KeybordKeyType::key_S);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveLeft,	tktk::KeybordKeyType::key_A);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveRight, tktk::KeybordKeyType::key_D);
	
	// シーンを追加する
	auto loadingSceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Loading,		tktk::SceneInitParam::create<Sht2D_LoadingScene>());
	auto titleSceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Title,		tktk::SceneInitParam::create<Sht2D_TitleScene>());
	auto stageSelectSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::StageSelect,	tktk::SceneInitParam::create<Sht2D_StageSelectScene>());
	auto gamePlaySceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::GamePlay,		tktk::SceneInitParam::create<Sht2D_GamePlayScene>());
	auto stage1SceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage1,		tktk::SceneInitParam::create<Sht2D_Stage1Scene>());
	auto stage2SceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage2,		tktk::SceneInitParam::create<Sht2D_Stage2Scene>());
	auto stage3SceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage3,		tktk::SceneInitParam::create<Sht2D_Stage3Scene>());
	auto resultSceneHandle		= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Result,		tktk::SceneInitParam::create<Sht2D_ResultScene>());
	
	// それぞれのシーンの終了時に消えるオブジェクトに付けるタグを設定する
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(loadingSceneHandle,		GameObjectTag::LoadingSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(titleSceneHandle,		GameObjectTag::TitleSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(stageSelectSceneHandle,	GameObjectTag::StageSelectSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(gamePlaySceneHandle,		GameObjectTag::GamePlaySceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(stage1SceneHandle,		GameObjectTag::Stage1SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(stage2SceneHandle,		GameObjectTag::Stage2SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(stage3SceneHandle,		GameObjectTag::Stage3SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(resultSceneHandle,		GameObjectTag::ResultSceneObject);
	
	// 読み込みシーンを有効にする
	tktk::DX12GameManager::enableScene(loadingSceneHandle);
	
	// 衝突判定の組み合わせを設定する
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,		CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::PlayerBullet,	CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::EnemyBullet,	CollisionGroup::Player);

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}