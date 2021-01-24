#include "Sht2D_StageSelectSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_StageSelectSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_StageSelectSceneMenu::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �X�e�[�W�Z���N�g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::StageSelectSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f))
        .create();

    // �X�e�[�W�Z���N�g���j���[�X�N���v�g
    gameObject->createComponent<Sht2D_StageSelectSceneMenuScript>();

    return gameObject;
}
