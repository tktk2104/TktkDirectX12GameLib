#include "Sht2D_GameClearText.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_GameClearTextScript.h"

tktk::GameObjectPtr Sht2D_GameClearText::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(tktkMath::Vector2(tktk::DX12Game::getDrawGameAreaSize().x / 2.0f, -256.0f))
        .create();

    // �e�L�X�g�`��R���|�[�l���g
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .fontId(FontId::Basic)
        .centerRate(tktkMath::Vector2(0.5f, 0.5f))
        .localPosition(tktkMath::Vector2(0.0f, -128.0f))
        .localScale(tktkMath::Vector2(2.0f, 2.0f))
        .initText("GameClear")
        .create();

    // �e�L�X�g�`��R���|�[�l���g
    tktk::TextDrawer2DMaker::makeStart(gameObject)
        .fontId(FontId::Basic)
        .centerRate(tktkMath::Vector2(0.5f, 0.5f))
        .localPosition(tktkMath::Vector2(0.0f, 128.0f))
        .initText("Push A Button")
        .create();

    // �Q�[���N���A���̃V�[���J�ڃR���|�[�l���g
    gameObject->createComponent<Sht2D_GameClearTextScript>();

    return gameObject;
}
