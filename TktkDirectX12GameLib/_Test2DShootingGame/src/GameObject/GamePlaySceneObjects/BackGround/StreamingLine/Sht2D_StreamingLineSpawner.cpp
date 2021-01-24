#include "Sht2D_StreamingLineSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_StreamingLineSpawnerScript.h"

tktk::GameObjectPtr Sht2D_StreamingLineSpawner::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    gameObject->createComponent<Sht2D_StreamingLineSpawnerScript>();

    return gameObject;
}
