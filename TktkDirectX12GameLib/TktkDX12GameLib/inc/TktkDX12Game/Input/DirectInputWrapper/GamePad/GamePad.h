#ifndef GAME_PAD_H_
#define GAME_PAD_H_

#include <memory>
#include <array>
#include <TktkMath/Structs/Vector2.h>
#include "../DirectInputIncluder.h"
#include "GamePadBtnType.h"

namespace tktk
{
	class GamePad
	{
	public:

		GamePad(LPDIRECTINPUT8 input, HWND handle);
		~GamePad();

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
#endif // !GAME_PAD_H_