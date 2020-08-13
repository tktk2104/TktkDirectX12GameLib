#ifndef KEY_BOARD_UPDATER_H_
#define KEY_BOARD_UPDATER_H_

#include <array>
#include "../DirectInputIncluder.h"
#include "KeybordKeyType.h"

namespace tktk
{
	// キーボードの入力を検知するクラス
	class Keyboard
	{
	public:

		Keyboard(LPDIRECTINPUT8 input, HWND handle);
		~Keyboard();

		Keyboard(const Keyboard& other) = delete;
		Keyboard& operator = (const Keyboard& other) = delete;

	public:

		void update();

	public:

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType) const;

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType) const;

	private:

		// インプットデバイス
		LPDIRECTINPUTDEVICE8 m_inputDevice{ nullptr };

		// 現在のキー入力情報
		std::array<unsigned char, 256U> m_curKeys;

		// 前フレームのキー入力情報
		std::array<unsigned char, 256U> m_preKeys;
	};
}
#endif // !KEY_BOARD_UPDATER_H_