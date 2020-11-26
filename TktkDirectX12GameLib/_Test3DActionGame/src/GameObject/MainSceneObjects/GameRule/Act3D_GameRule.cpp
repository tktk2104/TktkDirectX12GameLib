#include "Act3D_GameRule.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_GameRuleScripts.h"

tktk::GameObjectPtr Act3D_GameRule::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    gameObject->addGameObjectTag(GameObjectTag::GameRule);

    gameObject->createComponent<Act3D_GameRuleScripts>();

    return gameObject;
}
