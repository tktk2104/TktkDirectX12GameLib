#include "Sht2D_TitleSceneMenuScript.h"

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

void Sht2D_TitleSceneMenuScript::start()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│自作コンポーネントの内部で新たなオブジェクトを作る事も可能です。
    │　また、生成時に使用した「tktk::GameObjectPtr」型の変数の値を保持する事で、いつでもそのオブジェクトにアクセスできるようになります。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // メニューの要素を作り、そのポインタを配列に保存する
    m_menuContantObjectArray = {  
        createMenuContant(tktkMath::Vector2(0.0f,   0.0f), tktkMath::Color_v::red,      "GameStart"),
        createMenuContant(tktkMath::Vector2(0.0f, 128.0f), tktkMath::Color_v::white,    "GameEnd")
    };


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│ゲームオブジェクトはお互いに親子関係を持つことができます。
    │　親子関係を持つ事で、子要素が親要素の座標を基準にして座標変換するようになったり、親要素の状態の一部を子供が共有する事になります。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // メニューの要素を自身の子要素に追加する
    getGameObject()->addChild(m_menuContantObjectArray.at(0U));
    getGameObject()->addChild(m_menuContantObjectArray.at(1U));
}

void Sht2D_TitleSceneMenuScript::update()
{
  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│入力の検知を行いたい時は、「tktk::DX12Game::isTrigger(inputType)」または「tktk::DX12Game::isPush(inputType)」を使って下さい。
    │　引数には「main.cpp」で設定した“入力の種類”の他、「tktk::KeybordKeyType」など個別の入力の種類を渡す事ができます。
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // 決定キーが押されたら
    if (tktk::DX12Game::isTrigger(CommandId::Decision))
    {
        auto local = m_menuContantObjectArray.at(0U)->getComponent<tktk::Transform2D>()->getLocalPosition(); // { 0.0f,   0.0f }

        auto world = m_menuContantObjectArray.at(0U)->getComponent<tktk::Transform2D>()->getWorldPosition(); // { 960.0f, 668.0f }

        // 現在のメニューの状態で分岐
        switch (m_curMenuState)
        {
        // “ゲームスタート”項目が選択されていたら
        case MenuContantType::GameStart:

            // ステージセレクトシーンへ移行
            tktk::DX12Game::enableScene(SceneId::StageSelect);
            tktk::DX12Game::disableScene(SceneId::Title);
            break;

        // “ゲーム終了”項目が選択されていたら
        case MenuContantType::GemeEnd:


          /*┌────────────────────────────────────────────────────────────────────────────────────────
	        │プログラムを終了したい場合は「 tktk::DX12Game::gameExit()」を使って下さい。
            │　現在のフレームの処理が終わり次第、各種リソースの後始末を終えた後、プログラムが終了します。
	        └────────────────────────────────────────────────────────────────────────────────────────*/

            // ゲームを終了する。
            tktk::DX12Game::gameExit();
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


  /*┌────────────────────────────────────────────────────────────────────────────────────────
	│移動入力の検知を行いたい時は、「tktk::DX12Game::getMoveInput()」を使って下さい。
    │　この関数ではゲームパッドの左スティックの入力と、「main.cpp」で設定した「WASDキー」の入力を取得できます。
    │　※回転移動入力の検知を行いたい時は「tktk::DX12Game::getLookInput()」を使って下さい。（この関数はゲームパッドの右スティックに対応しています）
	└────────────────────────────────────────────────────────────────────────────────────────*/

    // 現在の移動入力を取得する
    const tktkMath::Vector2& moveInput = tktk::DX12Game::getMoveInput();

    // ｙ方向の入力が -0.5より小さかったら
    if (moveInput.y < -0.5f)
    {
        // 次のメニューの種類を整数型で求める
        int nextMenuState = static_cast<int>(m_curMenuState) + 1;

        // 次のメニューの番号が有効な数字だったら
        if (nextMenuState <= static_cast<int>(MenuContantType::GemeEnd))
        {
            // 選択されているメニュー項目を更新する
            changeMenuState(nextMenuState);
        }
    }

    // ｙ方向の入力が 0.5より大きかったら
    else if (moveInput.y > 0.5f)
    {
        // 次のメニューの種類を整数型で求める
        int nextMenuState = static_cast<int>(m_curMenuState) - 1;

        // 次のメニューの番号が有効な数字だったら
        if (nextMenuState >= static_cast<int>(MenuContantType::GameStart))
        {
            // 選択されているメニュー項目を更新する
            changeMenuState(nextMenuState);
        }
    }
}

// 選択されているメニュー項目を更新する
void Sht2D_TitleSceneMenuScript::changeMenuState(int nextMenuState)
{
    // 現在のメニュー項目のオブジェクトを取得する
    const tktk::GameObjectPtr& preMenuContantObject = m_menuContantObjectArray.at(static_cast<size_t>(m_curMenuState));


  /*┌────────────────────────────────────────────────────────────────────────────────────────
    │特定のオブジェクトが持つコンポーネントを取得したい場合は、「gameObject->getComponent<T>()」を使って下さい。
    │　取得したコンポーネントは「tktk::ComponentPtr<T>」型の変数として扱えます。
    └────────────────────────────────────────────────────────────────────────────────────────*/

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