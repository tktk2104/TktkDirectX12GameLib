#ifndef COLLISION_GROUP_H_
#define COLLISION_GROUP_H_

// 衝突判定の組み合わせ
enum class CollisionGroup
{
	None,				// 衝突判定無し
	Player,				// プレイヤー
	Enemy,				// エネミー
	PlayerDamageRange,	// プレイヤーの攻撃範囲
	EnemyDamageRange,	// エネミーの攻撃範囲
	Stage				// ステージ
};
#endif // !COLLISION_GROUP_H_