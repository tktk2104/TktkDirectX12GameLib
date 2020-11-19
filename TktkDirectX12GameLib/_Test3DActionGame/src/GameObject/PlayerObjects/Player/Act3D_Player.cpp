#include "Act3D_Player.h"

#include "../../../Enums/Enums.h"
#include "../../CameraObjects/DefaultCamera/Act3D_DefaultCamera.h"

#include "Scripts/Act3D_PlayerController.h"
#include "Scripts/Act3D_InputToStartAttack.h"
#include "Scripts/Act3D_InputToStartComboAttack.h"
#include "Scripts/Act3D_JampAttackMoving.h"
#include "Scripts/Act3D_PlayerAttackRangeGenerator.h"
#include "Scripts/Act3D_PlayerCollisionReaction.h"
#include "Scripts/Act3D_PlayerDamager.h"
#include "Scripts/Act3D_PlayerEndAttack.h"
#include "Scripts/Act3D_PlayerEndDamage.h"

#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

// �ړ���Ԃ̐ݒ���s��
inline void createPlayerMoveSetting(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move });
    {
        // �v���C���[�ړ����A�ړ��X�e�[�g�ύX�R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerController>(2.0f, 45.0f);

        // �U���J�n���s���R���|�[�l���g
        gameObject->createComponent<Act3D_InputToStartAttack>();

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // �ҋ@��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::Idle });
    {
        // �ҋ@���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerIdle).lerpTimeSec(0.3f).create();
    }

    // �O��������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkForward });
    {
        // �O�������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkForward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // ���������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkBackward });
    {
        // ��������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkBackward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // ��������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal,  PlayerStateType::Move, PlayerStateType::WalkLeft });
    {
        // �������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkLeft).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // �E������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkRight });
    {
        // �E�����ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkRight).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    }

    // �O�������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::RunForward });
    {
        // �O������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerRunForward).lerpTimeSec(0.2f).motionSpeedRate(1.5f).create();
    }

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �U����Ԃ̐ݒ���s��
inline void createPlayerAttackSetting(tktk::GameObjectPtr gameObject)
{
    // �U���i�P�i�j��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack1 });
    {
        // �U���i�P�i�j�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.1f, 0.3f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // �P�i�ڂ���Q�i�ڂ̍U���ɑJ�ڂ���R���|�[�l���g
        gameObject->createComponent<Act3D_InputToStartComboAttack>(0.3f);

        // �U���i�P�i�j���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack1).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(2.0f).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.5f, PlayerStateType::Attack1);

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // �U���i�Q�i�j��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack2 });
    {
        // �U���i�Q�i�j�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.2f, 0.5f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // �U���i�Q�i�j���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack2).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(1.5f).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.8f, PlayerStateType::Attack2);

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // �W�����v�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::JumpAttack });
    {
        // �W�����v�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(1.0f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // �W�����v�U���ɂ��ړ��̃R���|�[�l���g
        gameObject->createComponent<Act3D_JampAttackMoving>(5.0f, 1.3f);

        // ���k����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::blue)
            .shrinkTargetPos({ 0.0f, 1.0f, 0.0f })
            .totalGenerateNum(20)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // �W�����v�U�����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerJumpAttack).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(2.0f, PlayerStateType::JumpAttack);
    }
   
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �_���[�W��Ԃ̐ݒ���s��
inline void createDamageAttackSetting(tktk::GameObjectPtr gameObject)
{
    // �U���i�P�i�j��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Damage });

    // �_���[�W�X�e�[�g���I�����鏈��
    gameObject->createComponent<Act3D_PlayerEndDamage>();

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
    tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDamage).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_Player::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // �v���C���[�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam initParam{};
    initParam.initRootNode({
            PlayerStateType::Normal,
            PlayerStateType::Damage,
            PlayerStateType::Dead
        });
    initParam.addChildNode({ PlayerStateType::Normal }, {
           PlayerStateType::Move,
           PlayerStateType::Attack
        });
    initParam.addChildNode({ PlayerStateType::Normal, PlayerStateType::Move }, {
            PlayerStateType::Idle,
            PlayerStateType::WalkForward,
            PlayerStateType::WalkBackward,
            PlayerStateType::WalkLeft,
            PlayerStateType::WalkRight,
            PlayerStateType::RunForward
        });
    initParam.addChildNode({ PlayerStateType::Normal, PlayerStateType::Attack },{
            PlayerStateType::Attack1,
            PlayerStateType::Attack2,
            PlayerStateType::JumpAttack
        });
    gameObject->setupStateMachine(initParam);

    // �ŏ��͈ړ��X�e�[�g
    gameObject->stateEnable(PlayerStateType::Normal);
    gameObject->stateEnable(PlayerStateType::Move);

    // �ړ���Ԃ̐ݒ���s��
    createPlayerMoveSetting(gameObject);

    // �U����Ԃ̐ݒ���s��
    createPlayerAttackSetting(gameObject);

    // �_���[�W��Ԃ̐ݒ���s��
    createDamageAttackSetting(gameObject);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // �R���������ړ��R���|�[�l���g
    tktk::InertialMovement3DMaker::makeStart(gameObject)
        .decelerationPerSec(1.0f)
        .craete();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::Player)
        .skeletonId(SkeletonId::Player)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // ���b�V���̃A�j���[�V�����R���|�[�l���g
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::PlayerIdle)
        .isLoop(true)
        .animFramePerSec(30.0f)
        .create();

    // OBB�Փ˔���R���|�[�l���g
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 0.8f, 1.6f, 0.8f })
        .localPosition({ 0.0f, 0.8f, 0.0f })
        .collisionGroupType(CollisionGroup::Player)
        .isExtrude(true)
        .extrudedRate(1.0f)
        .create();

// �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();
#endif // _DEBUG

    // �v���C���[�̏Փ˔���̃��A�N�V����
    gameObject->createComponent<Act3D_PlayerCollisionReaction>();

    // �d�͂ɂ��ړ��R���|�[�l���g
    gameObject->createComponent<Act3D_GravityMove>(3.0f);

    // �J���������g�̎q���ɐݒ肷��
    gameObject->addChild(Act3D_DefaultCamera::create({ 0.0f, 3.0f, -3.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -2.0f, 3.0f })));

    return gameObject;
}
