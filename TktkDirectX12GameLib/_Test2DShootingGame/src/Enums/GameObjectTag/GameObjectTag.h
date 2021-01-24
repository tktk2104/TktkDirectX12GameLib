#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

// ゲームオブジェクトを識別するためのタグ
enum class GameObjectTag
{
	LoadingSceneObject,		// ローディングシーン終了時に消滅するオブジェクト
	TitleSceneObject,		// タイトルシーン終了時に消滅するオブジェクト
	StageSelectSceneObject,	// ステージセレクトシーン終了時に消滅するオブジェクト
	GamePlaySceneObject,	// ゲームプレイシーン終了時に消滅するオブジェクト
	Stage1SceneObject,		// ステージ１シーン終了時に消滅するオブジェクト
	Stage2SceneObject,		// ステージ２シーン終了時に消滅するオブジェクト
	Stage3SceneObject,		// ステージ３シーン終了時に消滅するオブジェクト
	ResultSceneObject,		// リザルトシーン終了時に消滅するオブジェクト

	GameRule,				// ゲームルール
	ObjectSpawner,			// オブジェクトスポナー
	BaseBackGroundSpawner,	// 基地の背景スポナー

	Player,					// プレイヤー
	Enemy,					// エネミー
	Boss,					// ボス

	PlayerAttackRange,		// プレイヤーの攻撃範囲
	EnemyAttackRange,		// エネミーの攻撃範囲
};
#endif // !GAME_OBJECT_TAG_H_