#ifndef MOUSE_BUTTON_TYPE_H_
#define MOUSE_BUTTON_TYPE_H_

namespace tktk
{
	enum class MouseButtonType
	{
		leftBtn		= 0x01,	// 左クリック
		rightBtn	= 0x02,	// 右クリック
		centerBtn	= 0x04,	// 中央ボタン
	};
}
#endif // !MOUSE_BUTTON_TYPE_H_