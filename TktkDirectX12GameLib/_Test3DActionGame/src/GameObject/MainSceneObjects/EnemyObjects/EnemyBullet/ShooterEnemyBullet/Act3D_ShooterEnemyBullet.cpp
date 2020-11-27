#include "Act3D_ShooterEnemyBullet.h"

#include "../../../../../Enums/Enums.h"

#include "../../../../_CommonScripts/SelfDeadTimer/Act3D_SelfDeadTimer.h"
#include "../../_CommonEnemyScripts/Act3D_MoveForward.h"

tktk::GameObjectPtr Act3D_ShooterEnemyBullet::create(const tktkMath::Vector3& position, const tktkMath::Vector3& velocityPerSec)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // �G�l�~�[�e�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::EnemyBullet);

    // �G�l�~�[�U���͈̓^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(tktkMath::Quaternion::createLookRotation(velocityPerSec))
        .initScaleRate(1.0f)
        .create();

    // �P�F���b�V����`�悷��R���|�[�l���g
    tktk::MonoColorMeshDrawerMaker::makeStart(gameObject)
        .setSphereMeshWireFrame()
        .baseScale(0.2f)
        .albedoColor(tktkMath::Color_v::red)
        .create();

    // ���̏Փ˔���R���|�[�l���g
    tktk::SphereColliderMaker::makeStart(gameObject)
        .radius(0.1f)
        .collisionGroupType(CollisionGroup::EnemyDamageRange)
        .extrudedRate(0.0f)
        .create();

    // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
    tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
        .billboardMaterialId(BillBoardId::Spark)
        .billboardBlendRate(tktkMath::Color_v::red)
        .moveSpeedPerSec(0.5f)
        .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
        .create();

    // �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    /*tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();*/
#endif // _DEBUG

    // 10�b�ԂŎ��g���E���R���|�[�l���g
    gameObject->createComponent<Act3D_SelfDeadTimer>(10.0f);

    // �O���Ɉړ�����R���|�[�l���g
    gameObject->createComponent<Act3D_MoveForward>(velocityPerSec.length());

    return gameObject;
}