#include "Sht2D_StageSelectSceneLogo.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_StageSelectSceneLogo::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �X�e�[�W�Z���N�g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::StageSelectSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) - tktkMath::Vector2(0.0f, 256.0f))
        .initScaleRate(tktkMath::Vector2(1.5f, 1.5f))
        .create();

    // �e�L�X�g�`��R���|�[�l���g
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .fontId(FontId::Basic)
        .centerRate(tktkMath::Vector2(0.5f, 0.5f))
        .initText("StageSelect")
        .create();

    return gameObject;
}