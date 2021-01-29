#include "Sht2D_StreamingLineSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_StreamingLineSpawnerScript.h"

tktk::GameObjectPtr Sht2D_StreamingLineSpawner::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 流れる線を出現させるコンポーネント
    gameObject->createComponent<Sht2D_StreamingLineSpawnerScript>();

    return gameObject;
}
