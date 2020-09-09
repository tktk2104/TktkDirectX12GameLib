#include "TktkDX12Game/Input/DirectInputWrapper/Keyboard/Keyboard.h"

#include <algorithm>

namespace tktk
{
	Keyboard::Keyboard(LPDIRECTINPUT8 input, HWND handle)
	{
		// それぞれのキー入力情報を初期化する
		std::fill(std::begin(m_curKeys), std::end(m_curKeys), 0U);
		std::fill(std::begin(m_preKeys), std::end(m_preKeys), 0U);

		// デフォルトのシステムキーボードを使用する設定でデバイスを作成
		input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, NULL);

		// キーボードの入力デバイスである事を設定
		m_inputDevice->SetDataFormat(&c_dfDIKeyboard);

		// キーボードの排他制御をセットする
		m_inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		// 動作開始
		m_inputDevice->Acquire();
	}

	Keyboard::~Keyboard()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void Keyboard::update()
	{
		// 前フレームの入力状況を更新する
		std::copy(
			std::begin(m_curKeys),
			std::end(m_curKeys),
			std::begin(m_preKeys)
		);

#ifdef _M_AMD64 /* x64ビルドなら */

		// 入力の取得を試みる
		HRESULT ret = m_inputDevice->GetDeviceState(static_cast<unsigned int>(sizeof(unsigned char) * m_curKeys.size()), m_curKeys.data());

		// 入力動作が停止していた場合
		if (FAILED(ret))
		{
			// 動作を再開して再取得を試みる
			m_inputDevice->Acquire();
			m_inputDevice->GetDeviceState(static_cast<unsigned int>(sizeof(unsigned char) * m_curKeys.size()), m_curKeys.data());
		}
#else
		// 入力の取得を試みる
		HRESULT ret = m_inputDevice->GetDeviceState(sizeof(unsigned char) * m_curKeys.size(), m_curKeys.data());

		// 入力動作が停止していた場合
		if (FAILED(ret))
		{
			// 動作を再開して再取得を試みる
			m_inputDevice->Acquire();
			m_inputDevice->GetDeviceState(sizeof(unsigned char) * m_curKeys.size(), m_curKeys.data());
		}
#endif // _M_AMD64
	}

	bool Keyboard::isPush(KeybordKeyType keyType) const
	{
		return (m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80);
	}

	bool Keyboard::isTrigger(KeybordKeyType keyType) const
	{
		return ((m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80) && !(m_preKeys.at(static_cast<unsigned int>(keyType)) & 0x80));
	}
}