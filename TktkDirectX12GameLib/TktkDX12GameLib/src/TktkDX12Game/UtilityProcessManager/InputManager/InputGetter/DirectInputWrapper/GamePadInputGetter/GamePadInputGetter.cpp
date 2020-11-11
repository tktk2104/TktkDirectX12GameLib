#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadInputGetter.h"

#include <algorithm>

namespace tktk
{
	struct CallBackFuncArgs
	{
		LPDIRECTINPUT8			input		{ nullptr };
		LPDIRECTINPUTDEVICE8*	inputDevice	{ nullptr };
		HWND					handle		{ nullptr };
	};

	BOOL CALLBACK EnumJoyDeviceProc(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
	{
		CallBackFuncArgs* args = reinterpret_cast<CallBackFuncArgs*>(pContext);

		// ジョイスティックデバイスの作成
		HRESULT ret = args->input->CreateDevice(pdidInstance->guidInstance, args->inputDevice, NULL);
		if (FAILED(ret))
		{
			// デバイス作成失敗
			return DIENUM_STOP;
		}

		// 入力データ形式のセット
		ret = (*args->inputDevice)->SetDataFormat(&c_dfDIJoystick2);
		if (FAILED(ret))
		{
			// 入力データ形式のセット失敗
			(*args->inputDevice)->Release();
			return DIENUM_STOP;
		}

		// 排他制御のセット
		ret = (*args->inputDevice)->SetCooperativeLevel(args->handle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
		if (FAILED(ret))
		{
			// 排他制御のセット失敗
			(*args->inputDevice)->Release();
			return DIENUM_STOP;
		}

		// 入力範囲のセット
		DIPROPRANGE diprg;
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMax = 1000;
		diprg.lMin = -1000;

		// X軸
		diprg.diph.dwObj = DIJOFS_X;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// Y軸
		diprg.diph.dwObj = DIJOFS_Y;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// Z軸
		diprg.diph.dwObj = DIJOFS_Z;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RX軸
		diprg.diph.dwObj = DIJOFS_RX;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RY軸
		diprg.diph.dwObj = DIJOFS_RY;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// RZ軸
		diprg.diph.dwObj = DIJOFS_RZ;
		(*args->inputDevice)->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 起動準備完了
		(*args->inputDevice)->Poll();

		/* 構築完了なら
		DEBUG("インスタンスの登録名 [%s]\n", lpddi->tszInstanceName);
		DEBUG("製品の登録名         [%s]\n", lpddi->tszProductName);
		DEBUG("構築完了\n");*/

		// 最初の1つのみで終わる
		return DIENUM_STOP;         // 次のデバイスを列挙するにはDIENUM_CONTINUEを返す
	}

	GamePadInputGetter::GamePadInputGetter(LPDIRECTINPUT8 input, HWND handle, float padStickPlayWidth)
		: m_padStickPlayWidth(padStickPlayWidth)
	{
		// それぞれのキー入力情報を初期化する
		m_curPadState = std::make_unique<DIJOYSTATE2>();
		m_prePadState = std::make_unique<DIJOYSTATE2>();
		ZeroMemory(m_curPadState.get(), sizeof(DIJOYSTATE2));
		ZeroMemory(m_prePadState.get(), sizeof(DIJOYSTATE2));

		// コールバック関数に必要な引数
		CallBackFuncArgs callBackFuncArgs{ input, &m_inputDevice, handle };

		// 接続されているゲームパッドを探し、最初に見つけた物でデバイスを作成する
		input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyDeviceProc, &callBackFuncArgs, DIEDFL_ATTACHEDONLY);

		// ゲームパッドが接続されていたら
		if (m_inputDevice)
		{
			// ゲームパッド接続状態にする
			m_findGamePad = true;

			// 動作開始
			m_inputDevice->Acquire();
		}
	}

	GamePadInputGetter::~GamePadInputGetter()
	{
		if (m_inputDevice != nullptr)
		{
			m_inputDevice->Release();
		}
	}

	void GamePadInputGetter::update()
	{
		// コントローラーが接続されていなかったら何もしない
		if (!m_findGamePad) return;

		// 現在と１フレーム前の入力情報を入れ替える
		m_curPadState.swap(m_prePadState);

		// Pollを行う
		m_inputDevice->Poll();

		// 保険としてゼロクリアする
		ZeroMemory(m_curPadState.get(), sizeof(DIJOYSTATE2));

		// 入力の取得を試みる
		HRESULT ret = m_inputDevice->GetDeviceState(sizeof(DIJOYSTATE2), m_curPadState.get());

		// 入力動作が停止していた場合
		if (FAILED(ret))
		{
			// 動作を再開する
			m_inputDevice->Acquire();
		}
	}

	tktkMath::Vector2 GamePadInputGetter::getLstick() const
	{
		auto noPlayStickState = tktkMath::Vector2(static_cast<float>(m_curPadState->lX) / 1000.0f, static_cast<float>(m_curPadState->lY) / 1000.0f);

		if (noPlayStickState.length() < m_padStickPlayWidth) return tktkMath::Vector2_v::zero;

		return noPlayStickState;
	}

	tktkMath::Vector2 GamePadInputGetter::getRstick() const
	{
		auto noPlayStickState = tktkMath::Vector2(static_cast<float>(m_curPadState->lZ) / 1000.0f, static_cast<float>(m_curPadState->lRz) / 1000.0f);
		
		if (noPlayStickState.length() < m_padStickPlayWidth) return tktkMath::Vector2_v::zero;

		return noPlayStickState;
	}

	bool GamePadInputGetter::isPush(GamePadBtnType keyType) const
	{
		return (m_curPadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80);
	}

	bool GamePadInputGetter::isTrigger(GamePadBtnType keyType) const
	{
		return ((m_curPadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80) && !(m_prePadState->rgbButtons[static_cast<unsigned int>(keyType)] & 0x80));
	}
}