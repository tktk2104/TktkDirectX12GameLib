#ifndef MOUSE_UPDATER_H_
#define MOUSE_UPDATER_H_

#include <unordered_map>
#include <TktkMath/Structs/Vector2.h>
#include "MouseButtonType.h"

namespace tktk
{
	// マウス入力取得クラス
	class Mouse
	{
	public:

		Mouse();
		~Mouse() = default;

		Mouse(const Mouse& other) = delete;
		Mouse& operator = (const Mouse& other) = delete;

	public:

		void update();

	public:

		// 指定のボタンが押されているか
		bool isPush(MouseButtonType buttonType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseButtonType buttonType) const;

		// マウスカーソルの座標を取得する
		tktkMath::Vector2 mousePos() const;

	private:

		std::unordered_map<MouseButtonType, bool> m_curMouseButtonState;
		std::unordered_map<MouseButtonType, bool> m_preMouseButtonState;
	};
}
#endif // !MOUSE_UPDATER_H_
