#include "Sht2D_PlayerMissileCounter.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerMissileCounterScript.h"

tktk::GameObjectPtr Sht2D_PlayerMissileCounter::create(const tktkMath::Vector2& position)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(0.75f)
        .create();

    gameObject->createComponent<Sht2D_PlayerMissileCounterScript>();

    return gameObject;
}
