#ifndef MESH_ID_H_
#define MESH_ID_H_

// メッシュリソースID
enum class MeshId
{
	SkyBox,			// スカイボックス

	Player,			// プレイヤー

	FighterEnemy,	// 近接攻撃エネミー
	ShooterEnemy,	// 遠距離攻撃エネミー
	BossEnemy,		// ボスエネミー

	GrassBlock,
};
#endif // !MESH_ID_H_