#include "Sht2D_BaseBackGroundSpawnStopper.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnStopperScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawnStopper::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    gameObject->createComponent<Sht2D_BaseBackGroundSpawnStopperScript>();

    return gameObject;
}
