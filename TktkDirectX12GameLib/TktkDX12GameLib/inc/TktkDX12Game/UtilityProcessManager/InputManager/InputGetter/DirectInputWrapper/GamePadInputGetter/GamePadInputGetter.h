#ifndef GAME_PAD_INPUT_GETTER_H_
#define GAME_PAD_INPUT_GETTER_H_

/* std::unique_ptr */
#include <memory>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "GamePadBtnType.h"

namespace tktk
{
	// ゲームパッド入力検知クラス
	class GamePadInputGetter
	{
	public:

		GamePadInputGetter(LPDIRECTINPUT8 input, HWND handle, float padStickPlayWidth);
		~GamePadInputGetter();

	public:

		void update();

	public:

		// 左スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getLstick() const;

		// 右スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getRstick() const;

		// 指定のボタンが押されているかを判定
		bool isPush(GamePadBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		// ゲームパッドのアナログスティックの傾きの遊び
		float							m_padStickPlayWidth;

		// インプットデバイス
		LPDIRECTINPUTDEVICE8			m_inputDevice{ nullptr };

		// ゲームパッドを見つけたか？
		bool							m_findGamePad{ false };

		// 現在のパッド入力情報
		std::unique_ptr<DIJOYSTATE2>	m_curPadState;

		// 前フレームのパッド入力情報
		std::unique_ptr<DIJOYSTATE2>	m_prePadState;
	};
}
#endif // !GAME_PAD_INPUT_GETTER_H_