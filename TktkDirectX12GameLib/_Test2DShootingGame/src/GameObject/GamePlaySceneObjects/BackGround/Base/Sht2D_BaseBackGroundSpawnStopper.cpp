#include "Sht2D_BaseBackGroundSpawnStopper.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnStopperScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawnStopper::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // 基地の背景生成停止コンポーネント
    gameObject->createComponent<Sht2D_BaseBackGroundSpawnStopperScript>();

    return gameObject;
}
