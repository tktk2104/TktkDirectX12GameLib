#include "Act3D_GameRule.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Act3D_GameRuleScripts.h"

tktk::GameObjectPtr Act3D_GameRule::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���U���g�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::ResultSceneObject);

    // �Q�[�����[���I�u�W�F�N�g�^�O
    gameObject->addGameObjectTag(GameObjectTag::GameRule);

    // �Q�[�����[�����Ǘ�����R���|�[�l���g
    gameObject->createComponent<Act3D_GameRuleScripts>();

    return gameObject;
}
