#include "Sht2D_ObjectSpawner.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_ObjectSpawnerScript.h"

tktk::GameObjectPtr Sht2D_ObjectSpawner::create(const std::string& csvFilePath)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �I�u�W�F�N�g�X�|�i�[�ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::ObjectSpawner);

    // ���Ԍo�߂ŃI�u�W�F�N�g���o��������R���|�[�l���g
    gameObject->createComponent<Sht2D_ObjectSpawnerScript>(csvFilePath);

    return gameObject;
}
