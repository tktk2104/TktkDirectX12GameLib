#ifndef COMMAND_ID_H_
#define COMMAND_ID_H_

// プレイヤーが行える操作の種類
enum class CommandId
{
	Any,			// いずれかの入力

	MoveForward,	// 前方移動
	MoveBackward,	// 後方移動
	MoveLeft,		// 左移動
	MoveRight,		// 右移動

	LookLeft,		// 右視点移動
	LookRight,		// 左視点移動

	LookEnemy,		// 敵を見る

	Run,			// 走り移動

	Dodge,			// 回避

	Attack,			// 攻撃
};
#endif // !COMMAND_ID_H_