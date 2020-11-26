#include "Act3D_DebugSprite.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_DebugSprite::create(const tktkMath::Vector2& position)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Test)
        .create();

    return gameObject;
}
