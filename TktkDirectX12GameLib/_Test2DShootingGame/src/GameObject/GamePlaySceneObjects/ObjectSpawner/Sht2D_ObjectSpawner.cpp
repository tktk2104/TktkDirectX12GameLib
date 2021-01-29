#include "Sht2D_ObjectSpawner.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_ObjectSpawnerScript.h"

tktk::GameObjectPtr Sht2D_ObjectSpawner::create(const std::string& csvFilePath)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // オブジェクトスポナーであることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ObjectSpawner);

    // 時間経過でオブジェクトを出現させるコンポーネント
    gameObject->createComponent<Sht2D_ObjectSpawnerScript>(csvFilePath);

    return gameObject;
}
