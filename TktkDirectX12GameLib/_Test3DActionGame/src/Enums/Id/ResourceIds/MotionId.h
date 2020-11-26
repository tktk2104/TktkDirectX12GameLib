#ifndef MOTION_ID_H_
#define MOTION_ID_H_

enum class MotionId
{
	PlayerIdle,			// プレイヤー待機中
	PlayerWalkForward,	// プレイヤー前方歩き移動
	PlayerWalkBackward,	// プレイヤー後方歩き移動
	PlayerWalkLeft,		// プレイヤー左歩き移動
	PlayerWalkRight,	// プレイヤー左歩き移動
	PlayerRunForward,	// プレイヤー前方走り移動
	PlayerDodge,		// プレイヤー回避
	PlayerDamage,		// プレイヤーダメージ
	PlayerDead,			// プレイヤー死亡
	PlayerAttack1,		// プレイヤー横切り
	PlayerAttack2,		// プレイヤー縦切り
	PlayerJumpAttack,	// プレイヤージャンプ切り

	FighterEnemyIdle,			// 近接型エネミー待機中
	FighterEnemyStretchIdle,	// 近接型エネミー待機中伸び
	FighterEnemyWalk,			// 近接型エネミー歩き
	FighterEnemyRun,			// 近接型エネミー走り
	FighterEnemyPunch,			// 近接型エネミーパンチ
	FighterEnemySwiping,		// 近接型エネミー大振りパンチ
	FighterEnemyJumpAttack,		// 近接型エネミージャンプアタック
	FighterEnemyDamage,			// 近接型エネミーダメージ
	FighterEnemyDead,			// 近接型エネミー死亡

	ShooterEnemyIdle,	// 遠距離型エネミー待機中
	ShooterEnemyWalk,	// 遠距離型エネミー歩き
	ShooterEnemyAttack,	// 遠距離型エネミー近接攻撃
	ShooterEnemyShot,	// 遠距離型エネミー遠距離攻撃
	ShooterEnemyDamage,	// 遠距離型エネミーダメージ
	ShooterEnemyDead,	// 遠距離型エネミー死亡

	BossEnemyIlde,			// ボス型エネミー待機中
	BossEnemyRun,			// ボス型エネミー走り
	BossEnemyNormalAttack,	// ボス型エネミー通常攻撃
	BossEnemyJumpAttack,	// ボス型エネミージャンプ攻撃
	BossEnemyRoolAttack,	// ボス型エネミーローリング攻撃
	BossEnemyDown,			// ボス型エネミーローリングすっ転び
	BossEnemyStandUp,		// ボス型エネミー起き上がり
	BossEnemyDead,			// ボス型エネミー死亡
};
#endif // !MOTION_ID_H_