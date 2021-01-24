#include "Sht2D_BaseBackGroundSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnerScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawner::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    gameObject->addGameObjectTag(GameObjectTag::BaseBackGroundSpawner);

    gameObject->createComponent<Sht2D_BaseBackGroundSpawnerScript>();

    return gameObject;
}
