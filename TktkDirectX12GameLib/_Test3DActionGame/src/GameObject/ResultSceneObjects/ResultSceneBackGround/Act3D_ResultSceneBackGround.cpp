#include "Act3D_ResultSceneBackGround.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_ResultSceneBackGroundScript.h"

tktk::GameObjectPtr Act3D_ResultSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getDrawGameAreaSize() / 2.0f)
        .create();

    // �Q�[���̏󋵂ɂ��\�����e��ω�������R���|�[�l���g
    gameObject->createComponent<Act3D_ResultSceneBackGroundScript>();

    return gameObject;
}
