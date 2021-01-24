#include "Sht2D_ObjectSpawner.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_ObjectSpawnerScript.h"

tktk::GameObjectPtr Sht2D_ObjectSpawner::create(const std::string& csvFilePath)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    gameObject->addGameObjectTag(GameObjectTag::ObjectSpawner);

    gameObject->createComponent<Sht2D_ObjectSpawnerScript>(csvFilePath);

    return gameObject;
}
