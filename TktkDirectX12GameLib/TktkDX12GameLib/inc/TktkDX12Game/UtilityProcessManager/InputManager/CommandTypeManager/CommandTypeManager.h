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

		// �R�}���hID�ɑΉ�������͂̎�ނ��擾����
		const CommandIdTarget& getCommandTarget(CommandIdCarrier commandId) const;

		// �ړ��R�}���hID�ɑΉ�������͂̎�ނ��擾����
		const CommandIdTarget& getCommandTarget(DirectionCommandId directionCommandId) const;

	public:

		// �e����͂Ɠ��̓R�}���hID�����т���
		void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
		void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);
		
		// �e����͂ƈړ����̓R�}���hID�����т���
		void addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType);
		void addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType);
	
	private:

		// ��̓��͂̎��
		static CommandIdTarget EmptyTarget;

	private:

		// ���ꂼ��̓��͂̎�ނƓ��̓R�}���hID�̑Ή��\
		std::unordered_map<CommandIdCarrier, CommandIdTarget>		m_commandMap;

		// ���ꂼ��̓��͂̎�ނƈړ����̓R�}���hID�̑Ή��\
		std::unordered_map<DirectionCommandId, CommandIdTarget>	m_directionCommandMap;
	};
}
#endif // !COMMAND_TYPE_MANAGER_H_