#include "Sht2D_StageSelectSceneLogo.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_StageSelectSceneLogo::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ステージセレクトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::StageSelectSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) - tktkMath::Vector2(0.0f, 256.0f))
        .initScaleRate(1.5f)
        .create();

    // テキスト描画コンポーネント
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .drawPriority(8)
        .fontId(FontId::Basic)
        .centerRate(0.5f)
        .initText("StageSelect")
        .create();

    return gameObject;
}