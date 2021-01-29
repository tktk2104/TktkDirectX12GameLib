#include "Sht2D_BaseBackGroundSpawner.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_BaseBackGroundSpawnerScript.h"

tktk::GameObjectPtr Sht2D_BaseBackGroundSpawner::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // ��n�̔w�i�I�u�W�F�N�g�X�|�i�[�ł��鎖��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::BaseBackGroundSpawner);

    // ��n�̔w�i���o��������R���|�[�l���g
    gameObject->createComponent<Sht2D_BaseBackGroundSpawnerScript>();

    return gameObject;
}
