#ifndef SPREAD_BULLET_ENEMY_STATE_H_
#define SPREAD_BULLET_ENEMY_STATE_H_

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