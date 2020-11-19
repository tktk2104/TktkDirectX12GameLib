#ifndef SHOOTER_ENEMY_STATE_TYPE_H_
#define SHOOTER_ENEMY_STATE_TYPE_H_

enum class ShooterEnemyStateType
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

	/* 攻撃ステート */
	Attack_1,		// 近距離攻撃ステート
	Shot,			// 遠距離攻撃ステート
};
#endif // !SHOOTER_ENEMY_STATE_TYPE_H_