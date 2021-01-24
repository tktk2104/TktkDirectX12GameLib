#include "Sht2D_GameRuleObject.h"

#include "../../Enums/Enums.h"
#include "Scripts/Sht2D_GameRuleScript.h"

tktk::GameObjectPtr Sht2D_GameRuleObject::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    gameObject->createComponent<Sht2D_GameRuleScript>();

    return gameObject;
}
