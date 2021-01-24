#include "Sht2D_PlayerMissileCounter.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerMissileCounterScript.h"

tktk::GameObjectPtr Sht2D_PlayerMissileCounter::create(const tktkMath::Vector2& position)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(0.75f)
        .create();

    gameObject->createComponent<Sht2D_PlayerMissileCounterScript>();

    return gameObject;
}