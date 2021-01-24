#ifndef COMMAND_ID_H_
#define COMMAND_ID_H_

// プレイヤーが行える操作の種類
enum class CommandId
{
	Decision,		// 決定

	ShotBullet,		// 弾発射
	ShotMissile,	// ミサイル発射
	ShotBomb,		// ボム発射
};
#endif // !COMMAND_ID_H_