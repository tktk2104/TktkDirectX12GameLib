#include "Sht2D_ResultSceneMenuScript.h"

#include "../../../../Enums/Enums.h"

namespace
{
    // メニューの要素を作る関数（生成座標、文字色、表示するテキスト）
    inline tktk::GameObjectPtr createMenuContant(const tktkMath::Vector2& position, const tktkMath::Color& color, const std::string& menuText)
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(position)
            .create();

        // テキスト描画コンポーネント
        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .centerRate(tktkMath::Vector2(0.5f, 0.5f))
            .blendRate(color)
            .initText(menuText)
            .create();

        return gameObject;
    }
}

void Sht2D_ResultSceneMenuScript::start()
{
    // メニューの要素を作り、そのポインタを配列に保存する
    m_menuContantObjectArray = {
        createMenuContant(tktkMath::Vector2(0.0f,   0.0f), tktkMath::Color_v::red,      "BackToTitle"),
        createMenuContant(tktkMath::Vector2(0.0f, 128.0f), tktkMath::Color_v::white,    "BackToStageSelect")
    };

    // メニューの要素を自身の子要素に追加する
    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
}

void Sht2D_ResultSceneMenuScript::update()
{
    // 決定キーが押されたら
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        // 現在のメニューの状態で分岐
        switch (m_curMenuState)
        {
        // “タイトルに戻る”項目が選択されていたら
        case MenuContantType::BackToTitle:

            // タイトルシーンへ移行
            tktk::DX12Game::enableScene(SceneId::Title);
            tktk::DX12Game::disableScene(SceneId::Result);
            break;

        // “ステージセレクトに戻る”項目が選択されていたら
        case MenuContantType::BackToStageSelect:

            // ステージセレクトシーンへ移行
            tktk::DX12Game::enableScene(SceneId::StageSelect);
            tktk::DX12Game::disableScene(SceneId::Result);
            break;
        }
        return;
    }

    // メニュー項目の変更間隔タイマーカウントが０以上だったら
    if (m_changeMenuIntervalSecTimer > 0.0f)
    {
        // カウントダウンしてこの関数を終える
        m_changeMenuIntervalSecTimer -= tktk::DX12Game::deltaTime();
        return;
    }

    // 現在の移動入力を取得する
    const tktkMath::Vector2& moveInput = tktk::DX12Game::getMoveInput();

    // ｙ方向の入力が -0.5より小さかったら
    if (moveInput.y < -0.5f)
    {
        // 次のメニューの種類を整数型で求める
        int nextMenuState = static_cast<int>(m_curMenuState) + 1;

        // 次のメニューの番号が有効な数字だったら
        if (nextMenuState <= static_cast<int>(MenuContantType::BackToStageSelect))
        {
            // 選択されているメニュー項目を更新する
            changeMenuState(nextMenuState);
        }
    }

    // ｙ方向の入力が 0.5より大きかったら
    if (moveInput.y > 0.5f)
    {
        // 次のメニューの種類を整数型で求める
        int nextMenuState = static_cast<int>(m_curMenuState) - 1;

        // 次のメニューの番号が有効な数字だったら
        if (nextMenuState >= static_cast<int>(MenuContantType::BackToTitle))
        {
            // 選択されているメニュー項目を更新する
            changeMenuState(nextMenuState);
        }
    }
}

void Sht2D_ResultSceneMenuScript::changeMenuState(int nextMenuState)
{
    // 現在のメニュー項目のオブジェクトを取得する
    const tktk::GameObjectPtr& preMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    // 現在のメニュー項目のオブジェクトが所持するテキスト描画コンポーネントを取得する
    tktk::ComponentPtr<tktk::TextDrawer2D> preMenuContantTextDrawer = preMenuContantObject->getComponent<tktk::TextDrawer2D>();

    // 現在のメニュー項目のテキスト色を白にする
    preMenuContantTextDrawer->setBlendRate(tktkMath::Color_v::white);

    // 現在のメニュー項目を新しい項目に変更する
    m_curMenuState = static_cast<MenuContantType>(nextMenuState);

    // 新しいメニュー項目のオブジェクトを取得する
    const tktk::GameObjectPtr& nextMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));

    // 新しいメニュー項目のオブジェクトが所持するテキスト描画コンポーネントを取得する
    tktk::ComponentPtr<tktk::TextDrawer2D> nextMenuContantTextDrawer = nextMenuContantObject->getComponent<tktk::TextDrawer2D>();

    // 新しいメニュー項目のテキスト色を赤にする
    nextMenuContantTextDrawer->setBlendRate(tktkMath::Color_v::red);

    // メニュー項目の変更間隔タイマーを開始する
    m_changeMenuIntervalSecTimer = ChangeMenuIntervalTimeSec;
}
