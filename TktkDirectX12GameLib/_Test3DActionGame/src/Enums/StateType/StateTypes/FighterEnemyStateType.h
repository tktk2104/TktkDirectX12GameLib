#ifndef FIGHTER_ENEMY_STATE_TYPE_H_
#define FIGHTER_ENEMY_STATE_TYPE_H_

// 近接攻撃エネミーの状態の種類
enum class FighterEnemyState
{
	/* 基本状態 */
	Alive,	// 生存ステート
	Dead,	// 死亡ステート

	/* 生存ステート */
	Normal,	// 通常ステート
	Damage,	// 被ダメージステート

	/* 通常ステート */
	Idle,			// 待機ステート
	Move,			// 移動ステート
	Attack,			// 攻撃ステート	
	
	/* 移動ステート */
	Walk,	// 歩きステート
	Run,	// 走りステート

	/* 攻撃ステート */
	Punch,		// パンチ攻撃ステート
	Swiping,	// スワイプ攻撃ステート
	JumpAttack,	// ジャンプ攻撃ステート
};
#endif // !FIGHTER_ENEMY_STATE_TYPE_H_