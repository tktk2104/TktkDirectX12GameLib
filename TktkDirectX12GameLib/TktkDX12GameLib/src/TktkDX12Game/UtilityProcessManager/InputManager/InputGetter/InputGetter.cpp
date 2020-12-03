#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/InputGetter.h"

#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseInputGetter.h"
#include "TktkDX12Game/UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/DirectInputWrapper.h"

namespace tktk
{
    InputGetter::InputGetter(HINSTANCE hInstance, HWND handle, float padStickPlayWidth)
    {
        m_mouse                 = std::make_unique<MouseInputGetter>();
        m_directInputWrapper    = std::make_unique<DirectInputWrapper>(hInstance, handle, padStickPlayWidth);
    }

    // デストラクタを非インライン化する
    InputGetter::~InputGetter() = default;

    void InputGetter::update()
    {
        m_mouse->update();
        m_directInputWrapper->update();
    }

    bool InputGetter::isPush(MouseBtnType btnType) const
    {
        return m_mouse->isPush(btnType);
    }

    bool InputGetter::isTrigger(MouseBtnType btnType) const
    {
        return m_mouse->isTrigger(btnType);
    }

    tktkMath::Vector2 InputGetter::mousePos(HWND hWnd) const
    {
        return m_mouse->mousePos(hWnd);
    }

    bool InputGetter::isPush(KeybordKeyType keyType) const
    {
        return m_directInputWrapper->isPush(keyType);
    }

    bool InputGetter::isTrigger(KeybordKeyType keyType) const
    {
        return m_directInputWrapper->isTrigger(keyType);
    }

    tktkMath::Vector2 InputGetter::getLstick() const
    {
        return m_directInputWrapper->getLstick();
    }

    tktkMath::Vector2 InputGetter::getRstick() const
    {
        return m_directInputWrapper->getRstick();
    }

    bool InputGetter::isPush(GamePadBtnType btnType) const
    {
        return m_directInputWrapper->isPush(btnType);
    }

    bool InputGetter::isTrigger(GamePadBtnType btnType) const
    {
        return m_directInputWrapper->isTrigger(btnType);
    }
}