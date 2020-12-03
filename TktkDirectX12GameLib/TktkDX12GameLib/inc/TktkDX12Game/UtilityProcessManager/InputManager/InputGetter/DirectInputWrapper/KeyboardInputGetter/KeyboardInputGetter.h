#ifndef KEY_BOARD_INPUT_GETTER_H_
#define KEY_BOARD_INPUT_GETTER_H_

/* std::vector */
#include <vector>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include "KeybordKeyType.h"

namespace tktk
{
	// キーボードの入力を検知するクラス
	class KeyboardInputGetter
	{
	public:

		KeyboardInputGetter(LPDIRECTINPUT8 input, HWND handle);
		~KeyboardInputGetter();

		KeyboardInputGetter(const KeyboardInputGetter& other) = delete;
		KeyboardInputGetter& operator = (const KeyboardInputGetter& other) = delete;

	public:

		void update();

	public:

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType) const;

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType) const;

	private:

		// キー入力情報を保存する配列の要素数
		static constexpr size_t			KeyDataArraySize	{ 256U };

		// キー入力情報の総バイト数
		static constexpr unsigned int	KeyDataByteSize		{ sizeof(unsigned char) * KeyDataArraySize };

	private:

		// インプットデバイス
		LPDIRECTINPUTDEVICE8		m_inputDevice	{ nullptr };

		// 現在のキー入力情報
		std::vector<unsigned char>	m_curKeys		{};

		// 前フレームのキー入力情報
		std::vector<unsigned char>	m_preKeys		{};
	};
}
#endif // !KEY_BOARD_INPUT_GETTER_H_