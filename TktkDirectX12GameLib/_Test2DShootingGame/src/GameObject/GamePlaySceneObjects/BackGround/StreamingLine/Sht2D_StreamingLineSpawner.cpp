#include "Sht2D_StreamingLineSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_StreamingLineSpawnerScript.h"

tktk::GameObjectPtr Sht2D_StreamingLineSpawner::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // ���������o��������R���|�[�l���g
    gameObject->createComponent<Sht2D_StreamingLineSpawnerScript>();

    return gameObject;
}
