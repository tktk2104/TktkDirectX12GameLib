#include "Act3D_ShooterEnemy.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"

#include "Scripts/Act3D_ShooterEnemyParam.h"
#include "Scripts/Act3D_ShooterEnemyStartChase.h"
#include "Scripts/Act3D_ShooterEnemyStartAttack.h"
#include "Scripts/Act3D_ShooterEnemyBulletGenerator.h"
#include "Scripts/Act3D_ShooterEnemyEndAttack.h"
#include "Scripts/Act3D_ShooterEnemyEndDamage.h"
#include "Scripts/Act3D_ShooterEnemyDamager.h"

// �ҋ@��Ԃ̐ݒ���s��
inline void createShooterEnemyIdleSetting(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Idle });
    {
        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���Ĉړ���ԂɑJ�ڂ���R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyStartChase>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // �A�C�h�����[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyIdle).create();
    }
    // �ҋ@��Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ړ���Ԃ̐ݒ���s��
inline void createShooterEnemyMoveSetting(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Move });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(60.0f);

        // �O���ɐi�ރR���|�[�l���g�i������ԁj
        gameObject->createComponent<Act3D_MoveForward>(0.5f);

        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���čU����ԂɑJ�ڂ�����
        gameObject->createComponent<Act3D_ShooterEnemyStartAttack>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // �������[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyWalk).lerpTimeSec(0.1f).create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �U����Ԃ̐ݒ���s��
inline void createShooterEnemyAttackSetting(tktk::GameObjectPtr gameObject)
{
    // �ߋ����U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack, ShooterEnemyStateType::Attack_1 });
    {
        // 2.2�b��ɋߋ����U�����������ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_ShooterEnemyEndAttack>(2.2f, ShooterEnemyStateType::Attack_1);

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // �p���`�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.5f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // �p���`���[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyAttack).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // �������U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack, ShooterEnemyStateType::Shot });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(60.0f);

        // �Q�b��ɉ������U�����������ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_ShooterEnemyEndAttack>(2.0f, ShooterEnemyStateType::Shot);

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyDamager>();

        // �e���˃R���|�[�l���g
        gameObject->createComponent<Act3D_ShooterEnemyBulletGenerator>();

        // �X���C�v���[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyShot).isLoop(false).lerpTimeSec(0.5f).create();
    }

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ʏ��Ԃ̐ݒ���s��
inline void setShooterEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃ̐ݒ���s��
    createShooterEnemyIdleSetting(gameObject);

    // �ړ���Ԃ̐ݒ���s��
    createShooterEnemyMoveSetting(gameObject);

    // �U����Ԃ̐ݒ���s��
    createShooterEnemyAttackSetting(gameObject);
}

// �_���[�W��Ԃ̐ݒ���s��
inline void setShooterEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // �_���[�W��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Damage });
    {
        // �_���[�W�X�e�[�g���I�����鏈��
        gameObject->createComponent<Act3D_ShooterEnemyEndDamage>();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 1.0f, 0.4f, 0.0f, 1.0f }) // ���F
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(30)
            .totalGenerateNum(30)
            .changeAvtiveToReset(true)
            .create();

        // �_���[�W���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyDamage).lerpTimeSec(0.1f).isLoop(false).create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// ������Ԃ̐ݒ���s��
inline void setShooterEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // ������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Alive });
    {
        // �R���������ړ��R���|�[�l���g
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(1.0f)
            .craete();

        // OBB�Փ˔���R���|�[�l���g
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 1.0f, 2.0f, 1.0f })
            .localPosition({ 0.0f, 1.0f, 0.0f })
            .collisionGroupType(CollisionGroup::Enemy)
            .extrudedRate(0.5f)
            .isExtrude(true)
            .create();

        // �G�l�~�[�̏Փ˔���̃��A�N�V����
        gameObject->createComponent<Act3D_EnemyCollisionReaction>();

        // �d�͂ɂ��ړ��R���|�[�l���g
        gameObject->createComponent<Act3D_GravityMove>(3.0f);
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});

    // �ʏ��Ԃ̐ݒ���s��
    setShooterEnemyNormalState(gameObject);

    // �_���[�W��Ԃ̐ݒ���s��
    setShooterEnemyDamageState(gameObject);
}

// ���S��Ԃ̐ݒ���s��
inline void setShooterEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // ���S��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ ShooterEnemyStateType::Dead });
    {
        // ���S���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::ShooterEnemyDead).initFrame(30.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 1.0f, 0.4f, 0.0f, 1.0f }) // ���F
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(30)
            .totalGenerateNum(30)
            .changeAvtiveToReset(true)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_ShooterEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �G�l�~�[�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam initParam{};

    // �匳�̃X�e�[�g�́u�����v���u���S�v�̂ǂ��炩
    initParam.initRootNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Dead });

    // �u�����X�e�[�g�v�́u�ʏ�v�Ɓu�_���[�W�v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ ShooterEnemyStateType::Alive }, { ShooterEnemyStateType::Normal, ShooterEnemyStateType::Damage });

    // �u�����E�ʏ�X�e�[�g�v�ɂ́u�ҋ@�v�u�ړ��v�u�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal },
        { ShooterEnemyStateType::Idle, ShooterEnemyStateType::Move, ShooterEnemyStateType::Attack });

    // �u�����E�ʏ�E�U���X�e�[�g�v�ɂ́u�p���`�v�u�X���C�v�v�u�W�����v�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Attack },
        { ShooterEnemyStateType::Attack_1, ShooterEnemyStateType::Shot });

    // �X�e�[�g�}�V���̏�����
    gameObject->setupStateMachine(initParam);

    // �ŏ��́u�����E�ʏ�E�ҋ@�X�e�[�g�v
    gameObject->statesEnable({ ShooterEnemyStateType::Alive, ShooterEnemyStateType::Normal, ShooterEnemyStateType::Idle });

    // ������Ԃ̐ݒ���s��
    setShooterEnemyAliveState(gameObject);

    // ���S��Ԃ̐ݒ���s��
    setShooterEnemyDeadState(gameObject);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::ShooterEnemy)
        .skeletonId(SkeletonId::ShooterEnemy)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // ���b�V���̃A�j���[�V�����R���|�[�l���g
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::ShooterEnemyIdle)
        .isLoop(true)
        .animFramePerSec(30.0f)
        .create();

// �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();
#endif // _DEBUG

    // �G�l�~�[�̔\�͒l
    gameObject->createComponent<Act3D_ShooterEnemyParam>();

    return gameObject;
}
