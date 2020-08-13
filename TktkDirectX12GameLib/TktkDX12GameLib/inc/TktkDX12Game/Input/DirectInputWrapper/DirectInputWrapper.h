#ifndef DIRECT_INPUT_WRAPPER_H_
#define DIRECT_INPUT_WRAPPER_H_

#include <memory>
#include <Windows.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector2.h>
#include "DirectInputIncluder.h"
#include "Keyboard/KeybordKeyType.h"
#include "GamePad/GamePadBtnType.h"

namespace tktk
{
	class Keyboard;
	class GamePad;

	// ダイレクトインプットでの入力判定処理
	class DirectInputWrapper
	{
	public:

		DirectInputWrapper(HINSTANCE hInstance, HWND handle);
		~DirectInputWrapper();

	public:

		void update();

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

		// インプット
		LPDIRECTINPUT8 m_input;

		// キーボード
		std::unique_ptr<Keyboard>	m_keyboard;

		// ゲームパッド
		std::unique_ptr<GamePad>	m_gamePad;
	};
}
#endif // !DIRECT_INPUT_WRAPPER_H_