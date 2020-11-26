#ifndef BOSS_ENEMY_STATE_TYPE_H_
#define BOSS_ENEMY_STATE_TYPE_H_

enum class BossEnemyStateType
{
	/* 基本状態 */
	Alive,	// 生存ステート
	Dead,	// 死亡ステート

	/* 生存ステート */
	Normal,	// 通常ステート
	Down,	// ダウン中ステート

	/* 通常ステート */
	Idle,			// 待機ステート
	Move,			// 移動ステート
	Attack,			// 攻撃ステート	

	/* 攻撃ステート */
	NormalAttack,	// 通常攻撃ステート
	JumpAttack,		// ジャンプ攻撃ステート
	RollAttack,		// ローリング攻撃ステート
	MissRool,		// 失敗ローリングステート

	/* ダウン中ステート */
	CantMove,	// 移動不能ステート
	StandUp,	// 起き上がりステート

	/* 特殊ステート */
	Damage,		// ダメージステートはどのステートとも同時に存在しうる
};
#endif // !BOSS_ENEMY_STATE_TYPE_H_