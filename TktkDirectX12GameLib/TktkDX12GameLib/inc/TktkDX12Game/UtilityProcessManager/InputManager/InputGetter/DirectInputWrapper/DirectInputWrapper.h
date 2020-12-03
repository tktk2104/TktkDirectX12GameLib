#ifndef DIRECT_INPUT_WRAPPER_H_
#define DIRECT_INPUT_WRAPPER_H_

/* std::unique_ptr */
#include <memory>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "KeyboardInputGetter/KeybordKeyType.h"
#include "GamePadInputGetter/GamePadBtnType.h"

namespace tktk
{
	// 前方宣言達
	class KeyboardInputGetter;
	class GamePadInputGetter;

	// ダイレクトインプットでの入力判定処理
	class DirectInputWrapper
	{
	public:

		DirectInputWrapper(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
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
		LPDIRECTINPUT8							m_input		{ nullptr };

		// キーボード
		std::unique_ptr<KeyboardInputGetter>	m_keyboard	{ nullptr };

		// ゲームパッド
		std::unique_ptr<GamePadInputGetter>		m_gamePad	{ nullptr };
	};
}
#endif // !DIRECT_INPUT_WRAPPER_H_