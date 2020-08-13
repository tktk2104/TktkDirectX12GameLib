#include "TktkDX12Game/Input/Mouse/Mouse.h"

#include <Windows.h>
#undef min
#undef max

namespace tktk
{
	Mouse::Mouse()
		: m_curMouseButtonState{ { MouseButtonType::leftBtn, false }, { MouseButtonType::rightBtn, false }, { MouseButtonType::centerBtn, false } }
		, m_preMouseButtonState{ m_curMouseButtonState }
	{
	}

	void Mouse::update()
	{
		std::swap(m_curMouseButtonState, m_preMouseButtonState);

		for (auto& pair : m_curMouseButtonState)
		{
			pair.second = GetAsyncKeyState(static_cast<int>(pair.first));
		}
	}

	tktkMath::Vector2 Mouse::mousePos() const
	{
		POINT tempMousePos;
		GetCursorPos(&tempMousePos);
		return { static_cast<float>(tempMousePos.x), static_cast<float>(tempMousePos.y) };
	}

	bool Mouse::isPush(MouseButtonType buttonType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (buttonType == MouseButtonType::leftBtn) return m_curMouseButtonState.at(MouseButtonType::rightBtn);
			if (buttonType == MouseButtonType::rightBtn) return m_curMouseButtonState.at(MouseButtonType::leftBtn);
		}
		return m_curMouseButtonState.at(buttonType);
	}

	bool Mouse::isTrigger(MouseButtonType buttonType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (buttonType == MouseButtonType::leftBtn) 
				return (m_curMouseButtonState.at(MouseButtonType::rightBtn) && !m_preMouseButtonState.at(MouseButtonType::rightBtn));

			if (buttonType == MouseButtonType::rightBtn) 
				return (m_curMouseButtonState.at(MouseButtonType::leftBtn) && !m_preMouseButtonState.at(MouseButtonType::leftBtn));
		}
		return (m_curMouseButtonState.at(buttonType) && !m_preMouseButtonState.at(buttonType));
	}
}