#ifndef DIRECTION_COMMAND_ID_H_
#define DIRECTION_COMMAND_ID_H_

namespace tktk
{
	// ˆÚ“®ƒRƒ}ƒ“ƒh
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