#include "Act3D_MainSceneChanger.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_MainSceneChangerScript.h"

tktk::GameObjectPtr Act3D_MainSceneChanger::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ウィンドウサイズを取得
    const auto& drawGameAreaSize = tktk::DX12Game::getDrawGameAreaSize();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(drawGameAreaSize / 2.0f)
        .initScaleRate({ drawGameAreaSize.x / 4.0f, drawGameAreaSize.y / 4.0f })
        .create();

    // フェード用スプライト
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(10)
        .spriteMaterialId(SpriteId::Black4x4)
        .blendRate({ 1.0f, 0.0f })
        .create();

    // メインシーンから遷移させる処理を行うコンポーネント
    gameObject->createComponent<Act3D_MainSceneChangerScript>();

    return gameObject;
}