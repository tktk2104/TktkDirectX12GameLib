#include "Sht2D_BaseBackGroundSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnerScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawner::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 基地の背景オブジェクトスポナーである事を表すタグ
    gameObject->addGameObjectTag(GameObjectTag::BaseBackGroundSpawner);

    // 基地の背景を出現させるコンポーネント
    gameObject->createComponent<Sht2D_BaseBackGroundSpawnerScript>();

    return gameObject;
}
