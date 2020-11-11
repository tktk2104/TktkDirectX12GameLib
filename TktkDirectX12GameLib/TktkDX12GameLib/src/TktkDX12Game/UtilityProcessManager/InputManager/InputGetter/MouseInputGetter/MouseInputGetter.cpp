#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseInputGetter.h"

namespace tktk
{
	MouseInputGetter::MouseInputGetter()
		: m_curMouseBtnState{ { MouseBtnType::leftBtn, false }, { MouseBtnType::rightBtn, false }, { MouseBtnType::centerBtn, false } }
		, m_preMouseBtnState{ m_curMouseBtnState }
	{
	}

	// デストラクタを非インライン化する
	MouseInputGetter::~MouseInputGetter() = default;

	void MouseInputGetter::update()
	{
		std::swap(m_curMouseBtnState, m_preMouseBtnState);

		for (auto& pair : m_curMouseBtnState)
		{
			pair.second = GetAsyncKeyState(static_cast<int>(pair.first));
		}
	}

	tktkMath::Vector2 MouseInputGetter::mousePos(HWND hWnd) const
	{
		POINT tempMousePos;
		GetCursorPos(&tempMousePos);
		ScreenToClient(hWnd, &tempMousePos);
		return { static_cast<float>(tempMousePos.x), static_cast<float>(tempMousePos.y) };
	}

	bool MouseInputGetter::isPush(MouseBtnType btnType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (btnType == MouseBtnType::leftBtn) return m_curMouseBtnState.at(MouseBtnType::rightBtn);
			if (btnType == MouseBtnType::rightBtn) return m_curMouseBtnState.at(MouseBtnType::leftBtn);
		}
		return m_curMouseBtnState.at(btnType);
	}

	bool MouseInputGetter::isTrigger(MouseBtnType btnType) const
	{
		if (GetSystemMetrics(SM_SWAPBUTTON))
		{
			if (btnType == MouseBtnType::leftBtn)
				return (m_curMouseBtnState.at(MouseBtnType::rightBtn) && !m_preMouseBtnState.at(MouseBtnType::rightBtn));

			if (btnType == MouseBtnType::rightBtn)
				return (m_preMouseBtnState.at(MouseBtnType::leftBtn) && !m_preMouseBtnState.at(MouseBtnType::leftBtn));
		}
		return (m_curMouseBtnState.at(btnType) && !m_preMouseBtnState.at(btnType));
	}
}