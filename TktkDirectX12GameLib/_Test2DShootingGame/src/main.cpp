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

namespace
{
	// 「DX12GameManager」の初期設定をする
	inline void setUpDX12GameManager(HINSTANCE hInstance, int nCmdShow)
	{
	  /*┌────────────────────────────────────────────────────────────────────────────────────────
		│TktkLibの初期化に必要な情報は「tktk::DX12GameManagerInitParam」構造体に詰まっています。
		│	※沢山の変数がありますが、最低限の情報＋αの説明は以下のコメントの通りです。
		└────────────────────────────────────────────────────────────────────────────────────────*/
		
		tktk::DX12GameManagerInitParam initParam{};

		// WinMain関数の引数をそのまま渡す
		initParam.windowParam.hInstance		= hInstance;
		initParam.windowParam.nCmdShow		= nCmdShow;
		// ゲームウィンドウの名前
		initParam.windowParam.windowName	= "Test2DShootingGame";
		// フルスクリーンフラグ
		initParam.windowParam.fullScreen	= false;
		// ゲーム画面の解像度
		initParam.windowParam.windowSize	= { 1920.0f, 1080.0f };

		// デバックレイヤーを無効にする
		initParam.createDebugLayer = false;

		// DX12GameManagerのセットアップ
		tktk::DX12GameManager::initialize(initParam);
	}
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
{
	// 「DX12GameManager」の初期設定をする
	setUpDX12GameManager(hInstance, nCmdShow);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│複数の種類の入力（キーボードorゲームパッドなど）を扱いたい時は、「tktk::DX12GameManager::addCommand(commandId, inputType)」で設定できます。
	│ゲームパッドのアナログスティック入力とその他の入力に互換性を持たせたい場合は「tktk::DX12GameManager::addDirectionCommand(directionCommand, inputType)」で設定できます。
	│　※「CommandId」は自分で作る列挙型、「tktk::DirectionCommandId」は事前に用意された列挙型になります。
	│　※設定可能な入力は「tktk::KeybordKeyType」でキーボード入力、「tktk::GamePadBtnType」でゲームパッド入力、「tktk::MouseBtnType」でマウス入力です。
	└────────────────────────────────────────────────────────────────────────────────────────*/
	
	// 各入力と入力コマンドを結びつける（入力コマンドの種類、対応する入力）
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::KeybordKeyType::key_Return);
	tktk::DX12GameManager::addCommand(CommandId::Decision,		tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::KeybordKeyType::key_Space);
	tktk::DX12GameManager::addCommand(CommandId::ShotBullet,	tktk::GamePadBtnType::btn_A);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::KeybordKeyType::key_M);
	tktk::DX12GameManager::addCommand(CommandId::ShotMissile,	tktk::GamePadBtnType::btn_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::KeybordKeyType::key_B);
	tktk::DX12GameManager::addCommand(CommandId::ShotBomb,		tktk::GamePadBtnType::btn_X);

	// 各入力と移動方向コマンドを結びつける（移動方向コマンドの種類、対応する入力）
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveUp,	tktk::KeybordKeyType::key_W);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveDown,	tktk::KeybordKeyType::key_S);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveLeft,	tktk::KeybordKeyType::key_A);
	tktk::DX12GameManager::addDirectionCommand(tktk::DirectionCommandId::MoveRight, tktk::KeybordKeyType::key_D);
	

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│衝突判定の組み合わせの追加は「tktk::DX12GameManager::addCollisionGroup(collisionGroup, collisionGroup)」で行えます。
	│　※衝突判定グループは衝突判定コンポーネントを使用する時に使います。（詳しい説明は別ファイル参照）
	│　※「CollisionGroup」は自分で作る列挙型です。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// 衝突判定の組み合わせを設定する（１つめの衝突判定グループ、２つめの衝突判定グループ）
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::Player,		CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::PlayerBullet,	CollisionGroup::Enemy);
	tktk::DX12GameManager::addCollisionGroup(CollisionGroup::EnemyBullet,	CollisionGroup::Player);


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│シーンの設定は「tktk::DX12GameManager::addSceneAndAttachId(SceneId, SceneInitParam)」で行えます。
	│　※「tktk::SceneInitParam」は事前に用意された構造体で、専用の関数の「tktk::SceneInitParam::create<SceneType>(constructorArgs...)」で作成して下さい。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// シーンを追加する（シーンの種類、シーンの初期化構造体）
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Loading,		tktk::SceneInitParam::create<Sht2D_LoadingScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Title,			tktk::SceneInitParam::create<Sht2D_TitleScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::StageSelect,	tktk::SceneInitParam::create<Sht2D_StageSelectScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::GamePlay,		tktk::SceneInitParam::create<Sht2D_GamePlayScene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage1,			tktk::SceneInitParam::create<Sht2D_Stage1Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage2,			tktk::SceneInitParam::create<Sht2D_Stage2Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Stage3,			tktk::SceneInitParam::create<Sht2D_Stage3Scene>());
	tktk::DX12GameManager::addSceneAndAttachId(SceneId::Result,			tktk::SceneInitParam::create<Sht2D_ResultScene>());
	

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│シーンの終了時に特定のゲームオブジェクト（ゲームの要素）を削除したい時は事前に「tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(sceneHandle, objectTag)」で設定して下さい。
	│　※第一引数は「SceneId」ではなく、“シーンハンドル”なので注意しましょう。「tktk::DX12GameManager::getSceneHandle(SceneId)」で取得できます。
	│　※「GameObjectTag」は自分で作る列挙型で、設定したタイミングで削除したいゲームオブジェクトに必ず追加して下さい。（追加方法は別ファイル参照）
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// それぞれのシーンの終了時に消えるオブジェクトに付けるタグを設定する
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Loading),		GameObjectTag::LoadingSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Title),		GameObjectTag::TitleSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::StageSelect), GameObjectTag::StageSelectSceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::GamePlay),	GameObjectTag::GamePlaySceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage1),		GameObjectTag::Stage1SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage2),		GameObjectTag::Stage2SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Stage3),		GameObjectTag::Stage3SceneObject);
	tktk::DX12GameManager::setSceneEndDestroyGameObjectTag(tktk::DX12GameManager::getSceneHandle(SceneId::Result),		GameObjectTag::ResultSceneObject);
	

  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│シーンを有効にするには「tktk::DX12GameManager::enableScene(sceneHandle)」で行えます。
	│	※第一引数は「SceneId」ではなく、“シーンハンドル”なので注意しましょう。「tktk::DX12GameManager::getSceneHandle(SceneId)」で取得できます。
	│また、「tktk::DX12Game::enableScene(SceneId)」でも行えます。（こちらはSceneId指定になります。）
	│「tktk::DX12GameManager」はメインマネージャー、「tktk::DX12Game」はメインマネージャーの処理を扱いやすくする為のインターフェースです。
	└────────────────────────────────────────────────────────────────────────────────────────*/

	// 読み込みシーンを有効にする
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));
	

/*┌────────────────────────────────────────────────────────────────────────────────────────
  │以下の関数を呼ぶとフレームワークが動き始めます
  └────────────────────────────────────────────────────────────────────────────────────────*/

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}