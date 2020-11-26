#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

enum class GameObjectTag
{
	LoadingSceneObject,	// ローディングシーン終了時に消滅するオブジェクト
	TitleSceneObject,	// タイトルシーン終了時に消滅するオブジェクト
	MainSceneObject,	// メインシーン終了時に消滅するオブジェクト
	ResultSceneObject,	// リザルトシーン終了時に消滅するオブジェクト


	GameRule,			// ゲームルール

	Player,				// プレイヤー
	Enemy,				// エネミー
	Boss,				// ボス

	EnemyBullet,		// エネミーの弾

	PlayerAttackRange,	// プレイヤーの攻撃範囲
	EnemyAttackRange,	// エネミーの攻撃範囲


	PlayerCamera,		// プレイヤーカメラ
};
#endif // !GAME_OBJECT_TAG_H_