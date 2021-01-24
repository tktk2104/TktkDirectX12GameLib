#include "Sht2D_ResultSceneLogo.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_ResultSceneLogo::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) - tktkMath::Vector2(0.0f, 256.0f))
        .initScaleRate(2.0f)
        .create();

    // �e�L�X�g�`��R���|�[�l���g
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .drawPriority(8)
        .fontId(FontId::Basic)
        .centerRate(0.5f)
        .initText("Result")
        .create();

    return gameObject;
}
