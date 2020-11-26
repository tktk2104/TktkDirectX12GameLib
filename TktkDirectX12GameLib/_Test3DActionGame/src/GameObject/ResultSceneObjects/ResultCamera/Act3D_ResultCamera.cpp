#include "Act3D_ResultCamera.h"

#include "../../../Enums/Enums.h"

#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"

tktk::GameObjectPtr Act3D_ResultCamera::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // リザルトシーンでのみ生存するオブジェクトタグ
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // 座標管理コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .create();

    // カメラオブジェクトを子要素に
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 10.0f, -10.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
