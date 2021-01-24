#include "Sht2D_ResultSceneMenuScript.h"

#include "../../../../Enums/Enums.h"

namespace
{
    inline tktk::GameObjectPtr createMenuContant(const tktkMath::Vector2& position, const tktkMath::Vector2& scale, const std::string& menuText)
    {
        auto menuContant = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(menuContant)
            .initPosition(position)
            .initScaleRate(scale)
            .create();

        // テキスト描画コンポーネント
        tktk::TextDrawer2DMaker::makeStart(menuContant)
            .drawPriority(8)
            .fontId(FontId::Basic)
            .centerRate(0.5f)
            .initText(menuText)
            .create();

        return menuContant;
    }
}

void Sht2D_ResultSceneMenuScript::start()
{
    m_menuContantObjectArray.at(0U) = createMenuContant({ 0.0f,   0.0f }, { 1.5f, 1.5f }, "BackToTitle");
    m_menuContantObjectArray.at(1U) = createMenuContant({ 0.0f, 128.0f }, { 1.0f, 1.0f }, "BackToStageSelect");

    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
}

void Sht2D_ResultSceneMenuScript::update()
{
    // 決定キーが押されたら
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        switch (m_curMenuState)
        {
        case MenuContantType::BackToTitle:

            tktk::DX12Game::enableScene(SceneId::Title);
            tktk::DX12Game::disableScene(SceneId::Result);
            break;

        case MenuContantType::BackToStageSelect:

            tktk::DX12Game::enableScene(SceneId::StageSelect);
            tktk::DX12Game::disableScene(SceneId::Result);
            break;
        }
        return;
    }

    if (m_changeMenuIntervalSecTimer > 0.0f)
    {
        m_changeMenuIntervalSecTimer -= tktk::DX12Game::deltaTime();
        return;
    }

    const auto& moveInput = tktk::DX12Game::getMoveInput();

    if (moveInput.y < -0.5f)
    {
        int nextMenuState = static_cast<int>(m_curMenuState) + 1;

        if (nextMenuState <= static_cast<int>(MenuContantType::BackToStageSelect))
        {
            changeMenuState(nextMenuState);
        }
    }

    if (moveInput.y > 0.5f)
    {
        int nextMenuState = static_cast<int>(m_curMenuState) - 1;

        if (nextMenuState >= static_cast<int>(MenuContantType::BackToTitle))
        {
            changeMenuState(nextMenuState);
        }
    }
}

void Sht2D_ResultSceneMenuScript::changeMenuState(int nextMenuState)
{
    const auto& preMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    auto preMenuContantTransform = preMenuContantObject->getComponent<tktk::Transform2D>();

    preMenuContantTransform->setLocalScaleRate(1.0f);

    m_curMenuState = static_cast<MenuContantType>(nextMenuState);

    const auto& nextMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    auto nextMenuContantTransform = nextMenuContantObject->getComponent<tktk::Transform2D>();

    nextMenuContantTransform->setLocalScaleRate(1.5f);

    m_changeMenuIntervalSecTimer = ChangeMenuIntervalTimeSec;
}
