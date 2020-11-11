#ifndef INPUT_GETTER_H_
#define INPUT_GETTER_H_

/* std::unique_ptr */
#include <memory>

/* HINSTANCE, HWND */
#include <Windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "MouseInputGetter/MouseBtnType.h"
#include "DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"

namespace tktk
{
	class MouseInputGetter;
	class DirectInputWrapper;

	// 入力受付クラス
	class InputGetter
	{
	public:

		InputGetter(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~InputGetter();

	public:

		void update();

	public: /* マウス関連の処理 */

		// 指定のボタンが押されているか
		bool isPush(MouseBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseBtnType btnType) const;

		// マウスカーソルの座標を取得する
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	public: /* キーボード関連の処理 */

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType) const;

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType) const;

	public: /* ゲームパッド関連の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getLstick() const;

		// 右スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getRstick() const;

		// 指定のボタンが押されているかを判定
		bool isPush(GamePadBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		std::unique_ptr<MouseInputGetter>				m_mouse;
		std::unique_ptr<DirectInputWrapper> m_directInputWrapper;
	};
}
#endif // !INPUT_GETTER_H_