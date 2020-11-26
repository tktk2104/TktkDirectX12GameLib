#include "Act3D_TitleSceneBackGround.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_TitleSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getWindowSize() / 2.0f)
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8)
        .spriteMaterialId(SpriteId::TitleSceneBackGround)
        .create();

    return gameObject;
}
