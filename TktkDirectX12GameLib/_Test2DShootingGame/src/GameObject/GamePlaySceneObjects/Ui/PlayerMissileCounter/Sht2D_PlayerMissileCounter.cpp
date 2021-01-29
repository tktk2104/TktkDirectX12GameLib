#include "Sht2D_PlayerMissileCounter.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerMissileCounterScript.h"

tktk::GameObjectPtr Sht2D_PlayerMissileCounter::create(const tktkMath::Vector2& position)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(tktkMath::Vector2(0.75f, 0.75f))
        .create();

    // �v���C���[�~�T�C���̎c�e�������A�C�R����\������R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerMissileCounterScript>();

    return gameObject;
}
