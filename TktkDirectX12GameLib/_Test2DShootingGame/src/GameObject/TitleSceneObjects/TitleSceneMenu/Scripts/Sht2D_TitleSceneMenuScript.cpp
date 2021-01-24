#include "Sht2D_TitleSceneMenuScript.h"

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

void Sht2D_TitleSceneMenuScript::start()
{
    m_menuContantObjectArray.at(0U) = createMenuContant({ 0.0f,   0.0f }, { 1.5f, 1.5f }, "GameStart");
    m_menuContantObjectArray.at(1U) = createMenuContant({ 0.0f, 128.0f }, { 1.0f, 1.0f }, "GameEnd");

    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
}

void Sht2D_TitleSceneMenuScript::update()
{
    // 決定キーが押されたら
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        switch (m_curMenuState)
        {
        case MenuContantType::GameStart:

            tktk::DX12Game::enableScene(SceneId::StageSelect);
            tktk::DX12Game::disableScene(SceneId::Title);
            break;

        case MenuContantType::GemeEnd:

            tktk::DX12Game::gameExit();
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

        if (nextMenuState <= static_cast<int>(MenuContantType::GemeEnd))
        {
            changeMenuState(nextMenuState);
        }
    }

    if (moveInput.y > 0.5f)
    {
        int nextMenuState = static_cast<int>(m_curMenuState) - 1;

        if (nextMenuState >= static_cast<int>(MenuContantType::GameStart))
        {
            changeMenuState(nextMenuState);
        }
    }
}

void Sht2D_TitleSceneMenuScript::changeMenuState(int nextMenuState)
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