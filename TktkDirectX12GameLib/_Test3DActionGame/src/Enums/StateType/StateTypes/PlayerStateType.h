#ifndef PLAYER_STATE_TYPE_H_
#define PLAYER_STATE_TYPE_H_

enum class PlayerStateType
{
	/* 基本状態 */
	Normal,	// 通常ステート
	Damage,	// 被ダメージステート
	Dead,	// 死亡ステート

	/* 通常ステート */
	Move,	// 移動ステート
	Attack,	// 攻撃ステート

	/* 移動ステート */
	Idle,			// 待機ステート
	WalkForward,	// 前方移動ステート
	WalkBackward,	// 後方移動しテート
	WalkLeft,		// 左移動ステート
	WalkRight,		// 右移動ステート
	RunForward,		// 前方移動ステート

	/* 攻撃ステート */
	Attack1,		// 一段攻撃ステート
	Attack2,		// 二段攻撃ステート	
	JumpAttack,		// ジャンプ攻撃ステート
};
#endif // !PLAYER_STATE_TYPE_H_