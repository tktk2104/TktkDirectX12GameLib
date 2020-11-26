#include "Act3D_ResultCamera.h"

#include "../../../Enums/Enums.h"

#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"

tktk::GameObjectPtr Act3D_ResultCamera::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[���ł̂ݐ�������I�u�W�F�N�g�^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .create();

    // �J�����I�u�W�F�N�g���q�v�f��
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 10.0f, -10.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
