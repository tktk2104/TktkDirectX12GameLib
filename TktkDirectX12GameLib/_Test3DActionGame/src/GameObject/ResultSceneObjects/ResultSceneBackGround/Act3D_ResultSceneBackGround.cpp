#include "Act3D_ResultSceneBackGround.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneBackGroundScript.h"

tktk::GameObjectPtr Act3D_ResultSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getWindowSize() / 2.0f)
        .create();

    gameObject->createComponent<Act3D_ResultSceneBackGroundScript>();

    return gameObject;
}
