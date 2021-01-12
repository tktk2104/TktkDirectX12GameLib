#include "TktkDX12BaseComponents/2D/TextDrawer2D/TextDrawer2DMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    TextDrawer2DMaker TextDrawer2DMaker::m_self;

    TextDrawer2DMaker& TextDrawer2DMaker::makeStart(GameObjectPtr user)
    {
        // 変数を初期化する
        m_self = TextDrawer2DMaker();

        // 引数のユーザーを設定
        m_self.m_user = user;

        // 自身の参照を返す
        return m_self;
    }

    ComponentPtr<TextDrawer2D> TextDrawer2DMaker::create()
    {
        // コンポーネントを作成する
        return m_user->createComponent<TextDrawer2D>(
            m_drawPriority,
            m_fontHandle,
            m_initText,
            m_centerRate,
            m_blendRate
            );
    }

    TextDrawer2DMaker& TextDrawer2DMaker::drawPriority(float value)
    {
        // 値を設定して自身の参照を返す
        m_drawPriority = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::fontHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_fontHandle = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::fontId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_fontHandle = DX12GameManager::getFontHandle(value);
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::initText(const std::string& value)
    {
        // 値を設定して自身の参照を返す
        m_initText = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::centerRate(const tktkMath::Vector2& value)
    {
        // 値を設定して自身の参照を返す
        m_centerRate = value;
        return *this;
    }

    TextDrawer2DMaker& TextDrawer2DMaker::blendRate(const tktkMath::Color& value)
    {
        // 値を設定して自身の参照を返す
        m_blendRate = value;
        return *this;
    }
}