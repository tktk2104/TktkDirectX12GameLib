#ifndef COMMAND_ID_TARGET_H_
#define COMMAND_ID_TARGET_H_

/* std::unordered_set */
#include <unordered_set>

/* class member */
#include "../InputGetter/MouseInputGetter/MouseBtnType.h"
#include "../InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "../InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"

namespace tktk
{
	// コマンドIDの対象となる入力の種類の一覧
	struct CommandIdTarget
	{
		std::unordered_set<MouseBtnType>	m_mouseBtnTypeList;
		std::unordered_set<KeybordKeyType>	m_keybordKeyTypeList;
		std::unordered_set<GamePadBtnType>	m_gamePadBtnTypeList;
	};
}
#endif // !COMMAND_ID_TARGET_H_