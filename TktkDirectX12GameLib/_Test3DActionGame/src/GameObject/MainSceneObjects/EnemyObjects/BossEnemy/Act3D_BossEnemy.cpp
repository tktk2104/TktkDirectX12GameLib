#include "Act3D_BossEnemy.h"

#include "../../../../Enums/Enums.h"
#include "../../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_RotateToPlayerInTime.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/SelfDeadTimer/Act3D_SelfDeadTimer.h"

#include "Scripts/Act3D_BossEnemyParam.h"
#include "Scripts/Act3D_BossEnemyDamager.h"
#include "Scripts/Act3D_BossEnemyStartChase.h"
#include "Scripts/Act3D_BossEnemyStartAttack.h"
#include "Scripts/Act3D_BossEnemyStartDown.h"
#include "Scripts/Act3D_BossEnemyStartStandUp.h"
#include "Scripts/Act3D_BossEnemyEndAttack.h"
#include "Scripts/Act3D_BossEnemyEndDown.h"
#include "Scripts/Act3D_BossEnemyEndDamage.h"

// �ҋ@��Ԃ̐ݒ���s��
inline void setBossEnemyIdleState(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Idle });
    {
        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���Ĉړ���ԂɑJ�ڂ���R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyStartChase>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // �ҋ@���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyIlde).lerpTimeSec(0.1f).isLoop(true).create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ړ���Ԃ̐ݒ���s��
inline void setBossEnemyMoveState(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Move });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(180.0f);

        // �O���ɐi�ރR���|�[�l���g
        gameObject->createComponent<Act3D_MoveForward>(3.0f);

        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���čU����ԂɑJ�ڂ�����
        gameObject->createComponent<Act3D_BossEnemyStartAttack>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // �ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyRun).lerpTimeSec(0.1f).isLoop(true).motionSpeedRate(0.7f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerRun)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playIntervalSec(0.13f)
            .playCount(-1)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �U����Ԃ̐ݒ���s��
inline void setBossEnemyAttackState(tktk::GameObjectPtr gameObject)
{
    // �ʏ�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::NormalAttack });
    {
        // 1.5�b�ԃv���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayerInTime>(35.0f, 1.5f);

        // 3.3�b��ɒʏ�U������ړ���ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(3.3f, BossEnemyStateType::NormalAttack);

        // 1.5�b�`3.0�b�̊Ԓʏ�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.5f, 3.0f, tktkMath::Vector3(0.0f, 2.0f, 2.5f), tktkMath::Vector3(3.0f, 3.0f, 4.0f));

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // �ʏ�U�����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyNormalAttack).lerpTimeSec(0.1f).motionSpeedRate(0.8f).isLoop(false).create();
   
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyNormalAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.1f)
            .playCount(1)
            .create();
    }

    // �W�����v�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::JumpAttack });
    {
        // 1.8�b�ԃW�����v�U���ɂ��ړ����s���R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(5.0f, 0.5f, 8.0f, 1.8f);

        // �R�b��ɃW�����v�U������ړ���ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(3.0f, BossEnemyStateType::JumpAttack);

        // 1.4�b�`2.4�b�̊ԃW�����v�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.4f, 2.4f, tktkMath::Vector3(0.0f, 1.0f, 0.0f), tktkMath::Vector3(5.0f, 1.0f, 5.0f));

        // �W�����v�U�����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyJumpAttack).lerpTimeSec(0.1f).isLoop(false).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyJumpAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();

        // ���k����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .shrinkTargetPos({ 0.0f, 2.0f, 0.0f })
            .totalGenerateNum(30)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.5f, 0.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(2.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(6.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .totalGenerateNum(120)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();
    }

    // ���[�����O�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::RollAttack });
    {
        // 1.8�b�ԃ��[�����O�U���ɂ��ړ����s���R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(0.0f, 1.0f, 3.0f, 1.8f);

        // 1.5�b��Ƀ��[�����O�U������ړ���ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyEndAttack>(1.5f, BossEnemyStateType::RollAttack);

        // 0.0�b�`1.5�b�̊ԃ��[�����O�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.0f, 1.5f, tktkMath::Vector3(0.0f, 1.0f, 2.0f), tktkMath::Vector3(4.0f, 1.0f, 4.0f));

        // ���[�����O�U�����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyRoolAttack).lerpTimeSec(0.1f).isLoop(false).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyRollAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .billboardScale({ 0.3f, 0.3f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(6.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(20)
            .generateIntervalTimeSec(0.1f)
            .changeAvtiveToReset(true)
            .create();
    }

    // ���s���[�����O��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
    {
        // �W�����v�U���ɂ��ړ��̃R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(0.0f, 1.0f, 3.0f, 1.2f);

        // ���s���[�����O��Ԃ���_�E����ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyStartDown>();

         // �W�����v�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.0f, 1.0f, tktkMath::Vector3(0.0f, 1.0f, 2.0f), tktkMath::Vector3(4.0f, 1.0f, 4.0f));

        // ���s���[�����O���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyDown).lerpTimeSec(0.1f).isLoop(false).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::BossEnemyRollAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
            .playCount(1)
            .create();
    }

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ʏ��Ԃ̐ݒ���s��
inline void setBossEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃ̐ݒ���s��
    setBossEnemyIdleState(gameObject);

    // �ړ���Ԃ̐ݒ���s��
    setBossEnemyMoveState(gameObject);

    // �U����Ԃ̐ݒ���s��
    setBossEnemyAttackState(gameObject);
}

// �ړ��s�\��Ԃ̐ݒ���s��
inline void setBossEnemyCantMoveState(tktk::GameObjectPtr gameObject)
{
    // �ړ��s�\��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Down, BossEnemyStateType::CantMove });
    {
        // �s���s�\��Ԃ���N���オ���ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyStartStandUp>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyDamager>();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �N���オ���Ԃ̐ݒ���s��
inline void setBossEnemyStandUpState(tktk::GameObjectPtr gameObject)
{
    // �N���オ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive, BossEnemyStateType::Down, BossEnemyStateType::StandUp });
    {
        // �_�E����Ԃ��I���鏈����ݒ肷��
        gameObject->createComponent<Act3D_BossEnemyEndDown>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyDamager>();

        // �N���オ�胂�[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyStandUp).lerpTimeSec(0.1f).motionSpeedRate(0.8f).isLoop(false).create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �_�E����Ԃ̐ݒ���s��
inline void setBossEnemyDownState(tktk::GameObjectPtr gameObject)
{
    // �ړ��s�\��Ԃ̐ݒ���s��
    setBossEnemyCantMoveState(gameObject);

    // �N���オ���Ԃ̐ݒ���s��
    setBossEnemyStandUpState(gameObject);
}

// ������Ԃ̐ݒ���s��
inline void setBossEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // ������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Alive });
    {
        // �R���������ړ��R���|�[�l���g
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(1.0f)
            .craete();

        // OBB�Փ˔���R���|�[�l���g
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 3.0f, 6.0f, 3.0f })
            .localPosition({ 0.0f, 3.3f, 0.0f })
            .collisionGroupType(CollisionGroup::Enemy)
            .isExtrude(true)
            .extrudedRate(0.1f)
            .create();

        // �G�l�~�[�̏Փ˔���̃��A�N�V����
        gameObject->createComponent<Act3D_EnemyCollisionReaction>();

        // �d�͂ɂ��ړ��R���|�[�l���g
        gameObject->createComponent<Act3D_GravityMove>();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});

    // �ʏ��Ԃ̐ݒ���s��
    setBossEnemyNormalState(gameObject);

    // �_�E����Ԃ̐ݒ���s��
    setBossEnemyDownState(gameObject);
}

// ���S��Ԃ̐ݒ���s��
inline void setBossEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // ���S��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Dead });
    {
        // ���S���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::BossEnemyDead).lerpTimeSec(0.1f).isLoop(false).create();
    
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

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(10)
            .totalGenerateNum(10)
            .moveSpeedPerSec(1.0f)
            .billboardScale(0.3f)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.5f, 3.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(1.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(30)
            .totalGenerateNum(90)
            .firstGenerateTimeSec(2.4f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.0f, 3.0f })
            .generateLocalPosRandomRange({ 2.0f, 2.0f, 2.0f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(30)
            .totalGenerateNum(180)
            .firstGenerateTimeSec(2.4f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyDead)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // ��莞�Ԍ�Ɏ��g�������R���|�[�l���g
        gameObject->createComponent<Act3D_SelfDeadTimer>(9.0f);
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �_���[�W��Ԃ̐ݒ���s��
inline void setBossEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // �_���[�W��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ BossEnemyStateType::Damage });
    {
        // �_���[�W��Ԃ��I������R���|�[�l���g
        gameObject->createComponent<Act3D_BossEnemyEndDamage>();

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

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .generateLocalPos({ 0.0f, 1.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
            .lifeTimeSec(0.4f)
            .generateNumPerOnce(10)
            .totalGenerateNum(10)
            .moveSpeedPerSec(1.0f)
            .billboardScale(0.3f)
            .changeAvtiveToReset(true)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_BossEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // �G�l�~�[�^�O�ƃ{�X�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::Enemy);
    gameObject->addGameObjectTag(GameObjectTag::Boss);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam initParam{};

    // �匳�̃X�e�[�g�́u�����v���u���S�v�u�_���[�W�v�̂����ꂩ�i�_���[�W�X�e�[�g�̂݃C���M�����[�j
    initParam.initRootNode({ BossEnemyStateType::Alive, BossEnemyStateType::Dead, BossEnemyStateType::Damage });

    // �u�����X�e�[�g�v�́u�ʏ�v�Ɓu�_�E���v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ BossEnemyStateType::Alive }, { BossEnemyStateType::Normal, BossEnemyStateType::Down });

    // �u�����E�ʏ�X�e�[�g�v�ɂ́u�ҋ@�v�u�ړ��v�u�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Normal },
        { BossEnemyStateType::Idle, BossEnemyStateType::Move, BossEnemyStateType::Attack });

    // �u�����E�ʏ�E�U���X�e�[�g�v�ɂ́u�ʏ�U���v�u�W�����v�U���v�u���[�����O�U���v�u���s���[�����O�v�̂S�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Attack },
        { BossEnemyStateType::NormalAttack, BossEnemyStateType::JumpAttack, BossEnemyStateType::RollAttack, BossEnemyStateType::MissRool });

    // �u�����E�_�E���X�e�[�g�v�́u�ړ��s�\�v�Ɓu�N���オ��v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ BossEnemyStateType::Alive, BossEnemyStateType::Down },
        { BossEnemyStateType::CantMove, BossEnemyStateType::StandUp });

    // �X�e�[�g�}�V���̏�����
    gameObject->setupStateMachine(initParam);

    // �ŏ��́u�����E�ʏ�E�ҋ@�X�e�[�g�v
    gameObject->statesEnable({ BossEnemyStateType::Alive, BossEnemyStateType::Normal, BossEnemyStateType::Idle });

    // ������Ԃ̐ݒ���s��
    setBossEnemyAliveState(gameObject);

    // ���S��Ԃ̐ݒ���s��
    setBossEnemyDeadState(gameObject);

    // �_���[�W��Ԃ̐ݒ���s��
    setBossEnemyDamageState(gameObject);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(MeshId::BossEnemy)
        .skeletonId(SkeletonId::BossEnemy)
        .baseScale(0.3f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // ���b�V���̃A�j���[�V�����R���|�[�l���g
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::BossEnemyIlde)
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
    gameObject->createComponent<Act3D_BossEnemyParam>();

    return gameObject;
}