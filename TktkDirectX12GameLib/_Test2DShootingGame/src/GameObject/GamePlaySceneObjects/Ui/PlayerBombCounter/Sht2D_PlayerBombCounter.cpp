#include "Sht2D_PlayerBombCounter.h"

#include "../../../../Enums/Enums.h"

#include "Scripts/Sht2D_PlayerBombCounterScript.h"

tktk::GameObjectPtr Sht2D_PlayerBombCounter::create(const tktkMath::Vector2& position)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(tktkMath::Vector2(0.75f, 0.75f))
        .create();

    // プレイヤーボムの残弾数だけアイコンを表示するコンポーネント
    gameObject->createComponent<Sht2D_PlayerBombCounterScript>();

    return gameObject;
}
