#ifndef COLLISION_GROUP_H_
#define COLLISION_GROUP_H_

// 衝突判定の組み合わせ
enum class CollisionGroup
{
	None,				// 衝突判定無し
	Player,				// プレイヤー
	Enemy,				// エネミー
	PlayerBullet,		// プレイヤーの弾
	EnemyBullet,		// エネミーの弾
};
#endif // !COLLISION_GROUP_H_