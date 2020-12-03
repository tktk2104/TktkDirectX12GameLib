#include "TktkDX12Game/UtilityProcessManager/InputManager/CommandTypeManager/CommandTypeManager.h"

namespace tktk
{
    // ��̓��͂̎��
    CommandIdTarget CommandTypeManager::EmptyTarget;

    // �R���X�g���N�^���C�����C����
    CommandTypeManager::CommandTypeManager() = default;

    // �f�X�g���N�^���C�����C����
    CommandTypeManager::~CommandTypeManager() = default;

    const CommandIdTarget& CommandTypeManager::getCommandTarget(CommandIdCarrier commandId) const
    {
        if (m_commandMap.count(commandId) == 0U) return EmptyTarget;

        return m_commandMap.at(commandId);
    }

    const CommandIdTarget& CommandTypeManager::getCommandTarget(DirectionCommandId directionCommandId) const
    {
        if (m_directionCommandMap.count(directionCommandId) == 0U) return EmptyTarget;

        return m_directionCommandMap.at(directionCommandId);
    }

    void CommandTypeManager::addCommand(CommandIdCarrier commandId, MouseBtnType btnType)
    {
        if (m_commandMap.count(commandId) == 0U) m_commandMap.insert({ commandId, CommandIdTarget() });

        m_commandMap.at(commandId).m_mouseBtnTypeList.insert(btnType);
    }

    void CommandTypeManager::addCommand(CommandIdCarrier commandId, KeybordKeyType keyType)
    {
        if (m_commandMap.count(commandId) == 0U) m_commandMap.insert({ commandId, CommandIdTarget() });

        m_commandMap.at(commandId).m_keybordKeyTypeList.insert(keyType);
    }

    void CommandTypeManager::addCommand(CommandIdCarrier commandId, GamePadBtnType btnType)
    {
        if (m_commandMap.count(commandId) == 0U) m_commandMap.insert({ commandId, CommandIdTarget() });

        m_commandMap.at(commandId).m_gamePadBtnTypeList.insert(btnType);
    }

    void CommandTypeManager::addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType)
    {
        if (m_directionCommandMap.count(directionCommandId) == 0U) m_directionCommandMap.insert({ directionCommandId, CommandIdTarget() });

        m_directionCommandMap.at(directionCommandId).m_mouseBtnTypeList.insert(btnType);
    }

    void CommandTypeManager::addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType)
    {
        if (m_directionCommandMap.count(directionCommandId) == 0U) m_directionCommandMap.insert({ directionCommandId, CommandIdTarget() });

        m_directionCommandMap.at(directionCommandId).m_keybordKeyTypeList.insert(keyType);
    }

    void CommandTypeManager::addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType)
    {
        if (m_directionCommandMap.count(directionCommandId) == 0U) m_directionCommandMap.insert({ directionCommandId, CommandIdTarget() });

        m_directionCommandMap.at(directionCommandId).m_gamePadBtnTypeList.insert(btnType);
    }
}