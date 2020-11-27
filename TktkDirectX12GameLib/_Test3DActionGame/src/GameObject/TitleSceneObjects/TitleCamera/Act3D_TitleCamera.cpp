#include "Act3D_TitleCamera.h"

#include "../../../Enums/Enums.h"

#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"
#include "Scripts/Act3D_TitleCameraScript.h"

tktk::GameObjectPtr Act3D_TitleCamera::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �^�C�g���V�[�����I������Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject).create();

    // �^�C�g���J�����ړ��R���|�[�l���g
    gameObject->createComponent<Act3D_TitleCameraScript>();

    // �J�����I�u�W�F�N�g���q�v�f��
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 10.0f, -10.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
