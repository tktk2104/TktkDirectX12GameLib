#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/DirectInputWrapper.h"

#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeyboardInputGetter.h"
#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadInputGetter.h"

namespace tktk
{
	DirectInputWrapper::DirectInputWrapper(HINSTANCE hInstance, HWND handle, float padStickPlayWidth)
	{
		DirectInput8Create(
			hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)(&m_input),
			NULL
		);

		m_keyboard	= std::make_unique<KeyboardInputGetter>(m_input, handle);
		m_gamePad	= std::make_unique<GamePadInputGetter>(m_input, handle, padStickPlayWidth);
	}

	DirectInputWrapper::~DirectInputWrapper()
	{
		if (m_input != nullptr)
		{
			m_input->Release();
		}
	}

	void DirectInputWrapper::update()
	{
		m_keyboard->update();
		m_gamePad->update();
	}

	bool DirectInputWrapper::isPush(KeybordKeyType keyType) const
	{
		return m_keyboard->isPush(keyType);
	}

	bool DirectInputWrapper::isTrigger(KeybordKeyType keyType) const
	{
		return m_keyboard->isTrigger(keyType);
	}

	tktkMath::Vector2 DirectInputWrapper::getLstick() const
	{
		return m_gamePad->getLstick();
	}

	tktkMath::Vector2 DirectInputWrapper::getRstick() const
	{
		return m_gamePad->getRstick();
	}

	bool DirectInputWrapper::isPush(GamePadBtnType btnType) const
	{
		return m_gamePad->isPush(btnType);
	}

	bool DirectInputWrapper::isTrigger(GamePadBtnType btnType) const
	{
		return m_gamePad->isTrigger(btnType);
	}
}