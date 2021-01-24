#include "Sht2D_TitleSceneMenu.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_TitleSceneMenuScript.h"

tktk::GameObjectPtr Sht2D_TitleSceneMenu::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �^�C�g���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::TitleSceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition((tktk::DX12Game::getDrawGameAreaSize() / 2.0f) + tktkMath::Vector2(0.0f, 128.0f))
        .create();

    // �^�C�g�����j���[�X�N���v�g
    gameObject->createComponent<Sht2D_TitleSceneMenuScript>();

    return gameObject;
}
