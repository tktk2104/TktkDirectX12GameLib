#include <TktkDX12GameLibDefinition.h>

#include <Windows.h>
#undef min
#undef max

#include <TktkDX12GameLibInitializer.h>

#include "Scene/Act3D_LoadingScene.h"
#include "Scene/Act3D_TitleScene.h"
#include "Scene/Act3D_MainScene.h"

#include "Enums/Enums.h"

// 「DX12GameManager」の初期設定をする
inline void setUpDX12GameManager(HINSTANCE hInstance, int nCmdShow)
{
	tktk::DX12GameManagerInitParam initParam{};

	// ゲームウィンドウの設定
	initParam.windowParam.hInstance		= hInstance;
	initParam.windowParam.nCmdShow		= nCmdShow;
	initParam.windowParam.windowName	= "Test3DActionGame";
	initParam.windowParam.windowSize	= { 1920.0f, 1080.0f };

	// デバックレイヤーを無効にする
	initParam.craeteDebugLayer = false;

	// DX12GameManagerのセットアップ
	tktk::DX12GameManager::initialize(initParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// 「DX12GameManager」の初期設定をする
	setUpDX12GameManager(hInstance, nCmdShow);

	// シーンを追加する
	auto loadingSceneHandle = tktk::DX12GameManager::addSceneAndAttachId(SceneId::Loading,	tktk::SceneInitParam::create<Act3D_LoadingScene>());
	auto titleSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Title,	tktk::SceneInitParam::create<Act3D_TitleScene>());
	auto mainSceneHandle	= tktk::DX12GameManager::addSceneAndAttachId(SceneId::Main,		tktk::SceneInitParam::create<Act3D_MainScene>());

	// それぞれのシーンでのみ生存するオブジェクトに付けるタグを設定する
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(loadingSceneHandle,	GameObjectTag::LoadingSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(titleSceneHandle,	GameObjectTag::TitleSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(mainSceneHandle,		GameObjectTag::MainSceneObject);

	// 読み込みシーンを有効にする
	tktk::DX12GameManager::enableScene(loadingSceneHandle);

	// 衝突判定の組み合わせを設定する
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::Stage);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Enemy,		CollisionGroup::Stage);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,	CollisionGroup::EnemyDamageRange);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Enemy,		CollisionGroup::PlayerDamageRange);

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}