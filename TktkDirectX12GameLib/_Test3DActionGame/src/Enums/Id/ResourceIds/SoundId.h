#ifndef SOUND_ID_H_
#define SOUND_ID_H_

// サウンドリソースID
enum class SoundId
{
	/* BGM */
	TitleBGM,		// タイトルBGM
	GamePlayBGM,	// ゲームプレイBGM
	ResultBGM,		// リザルトBGM

	/* SE */
	PlayerWalk,			// プレイヤー歩きサウンド
	PlayerRun,			// プレイヤー走りサウンド
	PlayerAttack1,		// プレイヤー一段目攻撃サウンド
	PlayerAttack2,		// プレイヤー二段目攻撃サウンド
	PlayerJumpAttack,	// プレイヤージャンプ攻撃サウンド
	PlayerDamage,		// プレイヤーダメージサウンド
	PlayerDead,			// プレイヤー死亡サウンド

	FighterEnemyAttack1,	// 近距離攻撃エネミー一段目攻撃サウンド
	FighterEnemyAttack2,	// 近距離攻撃エネミー二段目攻撃サウンド
	FighterEnemyJumpAttack,	// 近距離攻撃エネミージャンプ攻撃サウンド
	FighterEnemyDamage,		// 近距離攻撃エネミーダメージサウンド
	FighterEnemyDead,		// 近距離攻撃エネミー死亡サウンド

	ShooterEnemyAttack,	// 遠距離攻撃エネミー近距離攻撃サウンド
	ShooterEnemyShot,	// 遠距離攻撃エネミー遠距離攻撃サウンド
	ShooterEnemyDamage,	// 遠距離攻撃エネミーダメージサウンド
	ShooterEnemyDead,	// 遠距離攻撃エネミー死亡サウンド

	BossEnemyNormalAttack,	// ボスエネミー通常攻撃サウンド
	BossEnemyJumpAttack,	// ボスエネミージャンプ攻撃サウンド
	BossEnemyRollAttack,	// ボスエネミー回転攻撃サウンド
	BossEnemyDead,			// ボスエネミー死亡サウンド

	HeavyBlow,		// 重たい打撃音サウンド
	LightBlow,		// 軽い打撃音サウンド

	HeavySword,		// 重たい斬撃音サウンド
	MiddleSword,	// 普通の斬撃音サウンド
	LightSword,		// 軽い斬撃音サウンド

	Confirm,		// 決定サウンド
};
#endif // !SOUND_ID_H_