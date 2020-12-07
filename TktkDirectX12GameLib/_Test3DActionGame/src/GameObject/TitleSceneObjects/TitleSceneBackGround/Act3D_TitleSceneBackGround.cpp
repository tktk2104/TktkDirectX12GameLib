#include "Act3D_TitleSceneBackGround.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_TitleSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // タイトルシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getDrawGameAreaSize() / 2.0f)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8)
        .spriteMaterialId(SpriteId::TitleSceneBackGround)
        .create();

    return gameObject;
}
