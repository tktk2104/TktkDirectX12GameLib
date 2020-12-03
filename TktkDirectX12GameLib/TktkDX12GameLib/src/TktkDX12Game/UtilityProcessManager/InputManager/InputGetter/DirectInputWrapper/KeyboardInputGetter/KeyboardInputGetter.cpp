#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeyboardInputGetter.h"

#include <algorithm>

namespace tktk
{
	KeyboardInputGetter::KeyboardInputGetter(LPDIRECTINPUT8 input, HWND handle)
	{
		// それぞれのキー入力情報を初期化する
		m_curKeys = std::vector<unsigned char>(KeyDataArraySize, 0U);
		m_preKeys = std::vector<unsigned char>(KeyDataArraySize, 0U);

		// デフォルトのシステムキーボードを使用する設定でデバイスを作成
		input->CreateDevice(GUID_SysKeyboard, &m_inputDevice, NULL);

		// キーボードの入力デバイスである事を設定
		m_inputDevice->SetDataFormat(&c_dfDIKeyboard);

		// キーボードの排他制御をセットする
		m_inputDevice->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		// 動作開始
		m_inputDevice->Acquire();
	}

	KeyboardInputGetter::~KeyboardInputGetter()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void KeyboardInputGetter::update()
	{
		// 前フレームの入力状況を更新する
		m_preKeys.swap(m_curKeys);

		// 入力の取得を試みる
		HRESULT ret = m_inputDevice->GetDeviceState(KeyDataByteSize, m_curKeys.data());

		// 入力動作が停止していた場合
		if (FAILED(ret))
		{
			// 動作を再開して再取得を試みる
			m_inputDevice->Acquire();
			m_inputDevice->GetDeviceState(KeyDataByteSize, m_curKeys.data());
		}
	}

	bool KeyboardInputGetter::isPush(KeybordKeyType keyType) const
	{
		return (m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80);
	}

	bool KeyboardInputGetter::isTrigger(KeybordKeyType keyType) const
	{
		return ((m_curKeys.at(static_cast<unsigned int>(keyType)) & 0x80) && !(m_preKeys.at(static_cast<unsigned int>(keyType)) & 0x80));
	}
}