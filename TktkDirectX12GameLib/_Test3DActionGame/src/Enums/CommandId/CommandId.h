#ifndef COMMAND_ID_H_
#define COMMAND_ID_H_

enum class CommandId
{
	Any,			// いずれかの入力

	MoveForward,	// 前方移動
	MoveBackward,	// 後方移動
	MoveLeft,		// 左移動
	MoveRight,		// 右移動

	LookLeft,		// 右視点移動
	LookRight,		// 左視点移動

	Run,			// 走り移動

	Attack,			// 攻撃
};
#endif // !COMMAND_ID_H_