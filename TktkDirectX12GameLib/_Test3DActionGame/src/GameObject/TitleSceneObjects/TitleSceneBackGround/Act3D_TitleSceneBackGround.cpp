#include "Act3D_TitleSceneBackGround.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_TitleSceneBackGround::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �^�C�g���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktk::DX12Game::getDrawGameAreaSize() / 2.0f)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8)
        .spriteMaterialId(SpriteId::TitleSceneBackGround)
        .create();

    return gameObject;
}
