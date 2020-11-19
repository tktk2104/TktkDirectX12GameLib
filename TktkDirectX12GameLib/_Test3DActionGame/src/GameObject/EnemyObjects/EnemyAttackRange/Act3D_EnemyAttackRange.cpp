#include "Act3D_EnemyAttackRange.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_EnemyAttackRange::create(const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �G�l�~�[�U���͈̓^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(scale)
        .create();

    // OBB�Փ˔���R���|�[�l���g
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 1.0f, 1.0f, 1.0f })
        .localPosition({ 0.0f, 0.0f, 0.0f })
        .collisionGroupType(CollisionGroup::EnemyDamageRange)
        .extrudedRate(0.0f)
        .create();

    // �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();
#endif // _DEBUG

    return gameObject;
}
