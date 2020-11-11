#ifndef DIRECTION_COMMAND_ID_H_
#define DIRECTION_COMMAND_ID_H_

namespace tktk
{
	// �ړ��R�}���h
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