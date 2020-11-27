#include "Act3D_TitleCamera.h"

#include "../../../Enums/Enums.h"

#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"
#include "Scripts/Act3D_TitleCameraScript.h"

tktk::GameObjectPtr Act3D_TitleCamera::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // タイトルシーンが終了すると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // 座標管理コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject).create();

    // タイトルカメラ移動コンポーネント
    gameObject->createComponent<Act3D_TitleCameraScript>();

    // カメラオブジェクトを子要素に
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 10.0f, -10.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
