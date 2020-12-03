#ifndef MOUSE_BTN_TYPE_H_
#define MOUSE_BTN_TYPE_H_

namespace tktk
{
	enum class MouseBtnType
	{
		leftBtn		= 0x01,	// 左クリック
		rightBtn	= 0x02,	// 右クリック
		centerBtn	= 0x04,	// 中央ボタン
	};
}
#endif // !MOUSE_BTN_TYPE_H_