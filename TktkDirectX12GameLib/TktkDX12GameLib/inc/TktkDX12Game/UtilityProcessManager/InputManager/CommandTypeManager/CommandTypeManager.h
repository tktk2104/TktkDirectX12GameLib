#ifndef COMMAND_TYPE_MANAGER_H_
#define COMMAND_TYPE_MANAGER_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include "CommandIdCarrier.h"
#include "DirectionCommandId.h"
#include "CommandIdTarget.h"

namespace tktk
{
	class CommandTypeManager
	{
	public:

		CommandTypeManager();
		~CommandTypeManager();

	public:

		// コマンドIDに対応する入力の種類を取得する
		const CommandIdTarget& getCommandTarget(CommandIdCarrier commandId) const;

		// 移動コマンドIDに対応する入力の種類を取得する
		const CommandIdTarget& getCommandTarget(DirectionCommandId directionCommandId) const;

	public:

		// 各種入力と入力コマンドIDを結びつける
		void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
		void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);
		
		// 各種入力と移動入力コマンドIDを結びつける
		void addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType);
		void addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType);
	
	private:

		// 空の入力の種類
		static CommandIdTarget EmptyTarget;

	private:

		// それぞれの入力の種類と入力コマンドIDの対応表
		std::unordered_map<CommandIdCarrier, CommandIdTarget>		m_commandMap;

		// それぞれの入力の種類と移動入力コマンドIDの対応表
		std::unordered_map<DirectionCommandId, CommandIdTarget>	m_directionCommandMap;
	};
}
#endif // !COMMAND_TYPE_MANAGER_H_