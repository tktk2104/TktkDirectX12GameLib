#ifndef MOUSE_INPUT_GETTER_H_
#define MOUSE_INPUT_GETTER_H_

/* std::unordered_map */
#include <unordered_map>

/* HWND */
#include <windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "MouseBtnType.h"

namespace tktk
{
	// マウス入力取得クラス
	class MouseInputGetter
	{
	public:

		MouseInputGetter();
		~MouseInputGetter();

		MouseInputGetter(const MouseInputGetter& other) = delete;
		MouseInputGetter& operator = (const MouseInputGetter& other) = delete;

	public:

		void update();

	public:

		// 指定のボタンが押されているか
		bool isPush(MouseBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseBtnType btnType) const;

		// マウスカーソルの座標を取得する
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	private:

		std::unordered_map<MouseBtnType, bool> m_curMouseBtnState;
		std::unordered_map<MouseBtnType, bool> m_preMouseBtnState;
	};
}
#endif // !MOUSE_INPUT_GETTER_H_
