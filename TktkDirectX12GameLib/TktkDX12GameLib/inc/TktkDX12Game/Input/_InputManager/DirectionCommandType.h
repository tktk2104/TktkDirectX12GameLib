#ifndef DIRECTION_COMMAND_TYPE_H_
#define DIRECTION_COMMAND_TYPE_H_

namespace tktk
{
	// 移動コマンド
	enum class DirectionCommandType
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight,
		LookUp,
		LookDown,
		LookLeft,
		LookRight,
	};
}
#endif // !DIRECTION_COMMAND_TYPE_H_