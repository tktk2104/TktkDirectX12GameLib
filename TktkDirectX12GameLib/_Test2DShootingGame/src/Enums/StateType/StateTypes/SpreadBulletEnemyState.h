#ifndef SPREAD_BULLET_ENEMY_STATE_H_
#define SPREAD_BULLET_ENEMY_STATE_H_

// 拡散弾エネミーの状態の種類
enum class SpreadBulletEnemyState
{
	/* 基本ステート */
	Alive,	// 生存ステート
	Dead,	// 死亡ステート

	/* 生存ステート */
	Entry,
	Combat,
};
#endif // !SPREAD_BULLET_ENEMY_STATE_H_