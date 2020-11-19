#ifndef GAME_OBJECT_TAG_H_
#define GAME_OBJECT_TAG_H_

enum class GameObjectTag
{
	LoadingSceneObject,	// ローディングシーンでのみ生存するオブジェクト
	TitleSceneObject,	// タイトルシーンでのみ生存するオブジェクト
	MainSceneObject,	// メインシーンでのみ生存するオブジェクト


	Player,				// プレイヤー
	Enemy,				// エネミー
	Boss,				// ボス

	EnemyBullet,		// エネミーの弾

	PlayerAttackRange,	// プレイヤーの攻撃範囲
	EnemyAttackRange,	// エネミーの攻撃範囲
};
#endif // !GAME_OBJECT_TAG_H_