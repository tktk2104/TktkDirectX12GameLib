#include "TktkDX12Game/Input/_InputManager/InputManager.h"

#include <array>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	constexpr std::array<tktkMath::Vector2, 4U> DirArray{ tktkMath::Vector2_v::up, tktkMath::Vector2_v::down, tktkMath::Vector2_v::left, tktkMath::Vector2_v::right };

	InputManager::InputManager(float padStickPlayWidth)
		: m_padStickPlayWidth(padStickPlayWidth)
	{
	}

	void InputManager::update()
	{
		m_curMoveVec = DX12GameManager::getLstick();
		m_curLookVec = DX12GameManager::getRstick();

		if (m_curMoveVec.length() < m_padStickPlayWidth) m_curMoveVec = tktkMath::Vector2_v::zero;
		if (m_curLookVec.length() < m_padStickPlayWidth) m_curLookVec = tktkMath::Vector2_v::zero;

		for (const auto& pair : m_keyDirectionCommandMap)
		{
			if (!DX12GameManager::isKeybordPush(pair.second)) continue;

			auto directionCommand = static_cast<int>(pair.first);

			if (directionCommand < 4)
			{
				m_curMoveVec += DirArray.at(directionCommand);
			}
			else
			{
				m_curLookVec += DirArray.at(directionCommand - 4);
			}
		}

		for (const auto& pair : m_padDirectionCommandMap)
		{
			if (!DX12GameManager::isPadPush(pair.second)) continue;

			auto directionCommand = static_cast<int>(pair.first);

			if (directionCommand < 4)
			{
				m_curMoveVec += DirArray.at(directionCommand);
			}
			else
			{
				m_curLookVec += DirArray.at(directionCommand - 4);
			}
		}

		for (const auto& pair : m_mouseDirectionCommandeMap)
		{
			if (!DX12GameManager::isMousePush(pair.second)) continue;

			auto directionCommand = static_cast<int>(pair.first);

			if (directionCommand < 4)
			{
				m_curMoveVec += DirArray.at(directionCommand);
			}
			else
			{
				m_curLookVec += DirArray.at(directionCommand - 4);
			}
		}

		m_curMoveVec = m_curMoveVec.normalized();
		m_curLookVec = m_curLookVec.normalized();
	}

	bool InputManager::isPush(int commandId) const
	{
		auto keyMapRange = m_keyCommandMap.equal_range(commandId);

		for (auto itr = keyMapRange.first; itr != keyMapRange.second; itr++)
		{
			if (DX12GameManager::isKeybordPush((*itr).second)) return true;
		}

		auto padMapRange = m_padCommandMap.equal_range(commandId);

		for (auto itr = padMapRange.first; itr != padMapRange.second; itr++)
		{
			if (DX12GameManager::isPadPush((*itr).second)) return true;
		}

		auto mouseMapRange = m_mouseCommandMap.equal_range(commandId);

		for (auto itr = mouseMapRange.first; itr != mouseMapRange.second; itr++)
		{
			if (DX12GameManager::isMousePush((*itr).second)) return true;
		}

		return false;
	}

	bool InputManager::isTrigger(int commandId) const
	{
		auto keyMapRange = m_keyCommandMap.equal_range(commandId);

		for (auto itr = keyMapRange.first; itr != keyMapRange.second; itr++)
		{
			if (DX12GameManager::isKeybordTrigger((*itr).second)) return true;
		}

		auto padMapRange = m_padCommandMap.equal_range(commandId);

		for (auto itr = padMapRange.first; itr != padMapRange.second; itr++)
		{
			if (DX12GameManager::isPadTrigger((*itr).second)) return true;
		}

		auto mouseMapRange = m_mouseCommandMap.equal_range(commandId);

		for (auto itr = mouseMapRange.first; itr != mouseMapRange.second; itr++)
		{
			if (DX12GameManager::isMouseTrigger((*itr).second)) return true;
		}

		return false;
	}

	const tktkMath::Vector2& InputManager::moveVec() const
	{
		return m_curMoveVec;
	}

	const tktkMath::Vector2& InputManager::lookVec() const
	{
		return m_curLookVec;
	}

	void InputManager::addCommand(int commandId, KeybordKeyType keyType)
	{
		m_keyCommandMap.emplace(commandId, keyType);
	}

	void InputManager::addCommand(int commandId, GamePadBtnType btnType)
	{
		m_padCommandMap.emplace(commandId, btnType);
	}

	void InputManager::addCommand(int commandId, MouseButtonType btnType)
	{
		m_mouseCommandMap.emplace(commandId, btnType);
	}

	void InputManager::addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType)
	{
		m_keyDirectionCommandMap.emplace(directionCommand, keyType);
	}

	void InputManager::addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType)
	{
		m_padDirectionCommandMap.emplace(directionCommand, btnType);
	}

	void InputManager::addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType)
	{
		m_mouseDirectionCommandeMap.emplace(directionCommand, btnType);
	}
}