#include "Sht2D_ResultSceneLogo.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_ResultSceneLogo::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) - tktkMath::Vector2(0.0f, 256.0f))
        .initScaleRate(2.0f)
        .create();

    // テキスト描画コンポーネント
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .drawPriority(8)
        .fontId(FontId::Basic)
        .centerRate(0.5f)
        .initText("Result")
        .create();

    return gameObject;
}
