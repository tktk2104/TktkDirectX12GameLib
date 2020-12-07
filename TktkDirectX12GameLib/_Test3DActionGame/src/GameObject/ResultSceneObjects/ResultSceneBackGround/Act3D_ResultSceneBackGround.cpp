#include "Act3D_ResultSceneBackGround.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneBackGroundScript.h"

tktk::GameObjectPtr Act3D_ResultSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getDrawGameAreaSize() / 2.0f)
        .create();

    // ゲームの状況により表示内容を変化させるコンポーネント
    gameObject->createComponent<Act3D_ResultSceneBackGroundScript>();

    return gameObject;
}
