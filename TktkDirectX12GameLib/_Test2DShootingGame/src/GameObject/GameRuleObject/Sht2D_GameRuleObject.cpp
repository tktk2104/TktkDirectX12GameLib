#include "Sht2D_GameRuleObject.h"

#include "../../Enums/Enums.h"
#include "Scripts/Sht2D_GameRuleScript.h"

tktk::GameObjectPtr Sht2D_GameRuleObject::create()
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // �Q�[�����[���R���|�[�l���g
    gameObject->createComponent<Sht2D_GameRuleScript>();

    return gameObject;
}
