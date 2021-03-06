#ifndef DIRECTION_COMMAND_ID_H_
#define DIRECTION_COMMAND_ID_H_

namespace tktk
{
	// 移動コマンド
	enum class DirectionCommandId : unsigned int
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
#endif // !DIRECTION_COMMAND_ID_H_