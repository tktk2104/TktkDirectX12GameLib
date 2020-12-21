#include "TktkDX12Game/UtilityProcessManager/InputManager/InputManager.h"

#include <array>
#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/InputGetter.h"
#include "TktkDX12Game/UtilityProcessManager/InputManager/CommandTypeManager/CommandTypeManager.h"

namespace tktk
{
	// ベクトルに加算する処理を見やすくするための定数
	constexpr std::array<tktkMath::Vector2, 4U> DirArray{ tktkMath::Vector2_v::up, tktkMath::Vector2_v::down, tktkMath::Vector2_v::left, tktkMath::Vector2_v::right };

	// 移動コマンドの種類
	constexpr size_t MoveCommandIdCount { 4U };

	// 視点移動コマンドの種類
	constexpr size_t LookCommandIdCount{ 4U };

	InputManager::InputManager(HINSTANCE hInstance, HWND handle, float padStickPlayWidth)
	{
		m_inputGetter			= std::make_unique<InputGetter>(hInstance, handle, padStickPlayWidth);
		m_commandTypeManager	= std::make_unique<CommandTypeManager>();
	}

	// デストラクタを非インライン化する
	InputManager::~InputManager() = default;

	void InputManager::update()
	{
		m_inputGetter->update();

		m_curMoveVec = m_inputGetter->getLstick();
		m_curLookVec = m_inputGetter->getRstick();

		for (size_t directionCommandId = 0U; directionCommandId < MoveCommandIdCount; directionCommandId++)
		{
			const auto& commandIdTarget = m_commandTypeManager->getCommandTarget(static_cast<DirectionCommandId>(directionCommandId));

			for (const auto& btnType : commandIdTarget.m_mouseBtnTypeList)
			{
				if (m_inputGetter->isPush(btnType))
				{
					m_curMoveVec += DirArray.at(directionCommandId);
				}
			}
			for (const auto& keyType : commandIdTarget.m_keybordKeyTypeList)
			{
				if (m_inputGetter->isPush(keyType))
				{
					m_curMoveVec += DirArray.at(directionCommandId);
				}
			}
			for (const auto& btnType : commandIdTarget.m_gamePadBtnTypeList)
			{
				if (m_inputGetter->isPush(btnType))
				{
					m_curMoveVec += DirArray.at(directionCommandId);
				}
			}
		}

		for (size_t directionCommandId = 0U; directionCommandId < LookCommandIdCount; directionCommandId++)
		{
			const auto& commandIdTarget = m_commandTypeManager->getCommandTarget(static_cast<DirectionCommandId>(directionCommandId + 4U));

			for (const auto& btnType : commandIdTarget.m_mouseBtnTypeList)
			{
				if (m_inputGetter->isPush(btnType))
				{
					m_curLookVec += DirArray.at(directionCommandId);
				}
			}
			for (const auto& keyType : commandIdTarget.m_keybordKeyTypeList)
			{
				if (m_inputGetter->isPush(keyType))
				{
					m_curLookVec += DirArray.at(directionCommandId);
				}
			}
			for (const auto& btnType : commandIdTarget.m_gamePadBtnTypeList)
			{
				if (m_inputGetter->isPush(btnType))
				{
					m_curLookVec += DirArray.at(directionCommandId);
				}
			}
		}
		m_curMoveVec = m_curMoveVec.normalized();
		m_curLookVec = m_curLookVec.normalized();
	}

	bool InputManager::isPush(CommandIdCarrier commandId) const
	{
		const auto& commandIdTarget = m_commandTypeManager->getCommandTarget(commandId);

		for (const auto& btnType : commandIdTarget.m_mouseBtnTypeList)
		{
			if (m_inputGetter->isPush(btnType)) return true;
		}
		for (const auto& keyType : commandIdTarget.m_keybordKeyTypeList)
		{
			if (m_inputGetter->isPush(keyType)) return true;
		}
		for (const auto& btnType : commandIdTarget.m_gamePadBtnTypeList)
		{
			if (m_inputGetter->isPush(btnType)) return true;
		}
		return false;
	}

	bool InputManager::isTrigger(CommandIdCarrier commandId) const
	{
		const auto& commandIdTarget = m_commandTypeManager->getCommandTarget(commandId);

		for (const auto& btnType : commandIdTarget.m_mouseBtnTypeList)
		{
			if (m_inputGetter->isTrigger(btnType)) return true;
		}
		for (const auto& keyType : commandIdTarget.m_keybordKeyTypeList)
		{
			if (m_inputGetter->isTrigger(keyType)) return true;
		}
		for (const auto& btnType : commandIdTarget.m_gamePadBtnTypeList)
		{
			if (m_inputGetter->isTrigger(btnType)) return true;
		}
		return false;
	}

	const tktkMath::Vector2& InputManager::getMoveInput() const
	{
		return m_curMoveVec;
	}

	const tktkMath::Vector2& InputManager::getLookInput() const
	{
		return m_curLookVec;
	}

	bool InputManager::isPush(MouseBtnType btnType) const
	{
		return m_inputGetter->isPush(btnType);
	}

	bool InputManager::isTrigger(MouseBtnType btnType) const
	{
		return m_inputGetter->isTrigger(btnType);
	}

	tktkMath::Vector2 InputManager::mousePos(HWND hWnd) const
	{
		return m_inputGetter->mousePos(hWnd);
	}

	bool InputManager::isPush(KeybordKeyType keyType) const
	{
		return m_inputGetter->isPush(keyType);
	}

	bool InputManager::isTrigger(KeybordKeyType keyType) const
	{
		return m_inputGetter->isTrigger(keyType);
	}

	tktkMath::Vector2 InputManager::getLstick() const
	{
		return m_inputGetter->getLstick();
	}

	tktkMath::Vector2 InputManager::getRstick() const
	{
		return m_inputGetter->getRstick();
	}

	bool InputManager::isPush(GamePadBtnType btnType) const
	{
		return m_inputGetter->isPush(btnType);
	}

	bool InputManager::isTrigger(GamePadBtnType btnType) const
	{
		return m_inputGetter->isTrigger(btnType);
	}

	void InputManager::addCommand(CommandIdCarrier commandId, MouseBtnType btnType)
	{
		m_commandTypeManager->addCommand(commandId, btnType);
	}

	void InputManager::addCommand(CommandIdCarrier commandId, KeybordKeyType keyType)
	{
		m_commandTypeManager->addCommand(commandId, keyType);
	}

	void InputManager::addCommand(CommandIdCarrier commandId, GamePadBtnType btnType)
	{
		m_commandTypeManager->addCommand(commandId, btnType);
	}

	void InputManager::addDirectionCommand(DirectionCommandId directionCommand, MouseBtnType btnType)
	{
		m_commandTypeManager->addDirectionCommand(directionCommand, btnType);
	}

	void InputManager::addDirectionCommand(DirectionCommandId directionCommand, KeybordKeyType keyType)
	{
		m_commandTypeManager->addDirectionCommand(directionCommand, keyType);
	}

	void InputManager::addDirectionCommand(DirectionCommandId directionCommand, GamePadBtnType btnType)
	{
		m_commandTypeManager->addDirectionCommand(directionCommand, btnType);
	}
}