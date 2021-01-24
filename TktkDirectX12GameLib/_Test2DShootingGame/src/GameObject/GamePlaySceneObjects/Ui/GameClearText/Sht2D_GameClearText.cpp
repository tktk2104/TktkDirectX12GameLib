#include "Sht2D_GameClearText.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_GameClearTextScript.h"

tktk::GameObjectPtr Sht2D_GameClearText::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktkMath::Vector2(tktk::DX12Game::getDrawGameAreaSize().x / 2.0f, -256.0f))
        .initScaleRate(1.0f)
        .create();

    // テキスト描画コンポーネント
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .drawPriority(8)
        .fontId(FontId::Basic)
        .centerRate(0.5f)
        .localPosition({ 0.0f, -128.0f })
        .localScale(2.0f)
        .initText("GameClear")
        .create();

    // テキスト描画コンポーネント
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .drawPriority(8)
        .fontId(FontId::Basic)
        .centerRate(0.5f)
        .localPosition({ 0.0f, 128.0f })
        .initText("Push A Button")
        .create();

    gameObject->createComponent<Sht2D_GameClearTextScript>();

    return gameObject;
}
