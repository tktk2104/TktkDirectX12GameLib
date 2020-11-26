#include "Act3D_FighterEnemy.h"

#include "../../../Enums/Enums.h"
#include "../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../_CommonEnemyScripts/Act3D_RotateToPlayer.h"
#include "../_CommonEnemyScripts/Act3D_MoveForward.h"
#include "../_CommonEnemyScripts/Act3D_EnemyAttackRangeGenerator.h"
#include "../_CommonEnemyScripts/Act3D_EnemyJampAttackMoving.h"
#include "../_CommonEnemyScripts/Act3D_EnemyCollisionReaction.h"
#include "../_CommonEnemyScripts/Act3D_EnemyDeleteTimer.h"

#include "Scripts/Act3D_FighterEnemyParam.h"
#include "Scripts/Act3D_FighterEnemyDamager.h"
#include "Scripts/Act3D_FighterEnemyStartRun.h"
#include "Scripts/Act3D_FighterEnemyStartChase.h"
#include "Scripts/Act3D_FighterEnemyStartAttack.h"
#include "Scripts/Act3D_FighterEnemyStartComboAttack.h"
#include "Scripts/Act3D_FighterEnemyEndAttack.h"
#include "Scripts/Act3D_FighterEnemyEndDamage.h"

// �ҋ@��Ԃ̐ݒ���s��
inline void setFighterEnemyIdleState(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Idle });
    {
        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���ĕ�����ԂɑJ�ڂ���R���|�[�l���g
        gameObject->createComponent<Act3D_FighterEnemyStartChase>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_FighterEnemyDamager>();

        // �A�C�h�����[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyIdle).create();
    }
    // �ҋ@��Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ړ���Ԃ̐ݒ���s��
inline void setFighterEnemyMoveState(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(120.0f);

        // �v���C���[�Ƃ̈ʒu�֌W�ɂ���čU����ԂɑJ�ڂ�����
        gameObject->createComponent<Act3D_FighterEnemyStartAttack>();

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_FighterEnemyDamager>();
    }

    // ������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move, FighterEnemyState::Walk });
    {
        // �O���ɐi�ރR���|�[�l���g�i������ԁj
        gameObject->createComponent<Act3D_MoveForward>(1.0f);

        // �R�b��ɕ������瑖��Ɉڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_FighterEnemyStartRun>();

         // �������[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyWalk).lerpTimeSec(0.1f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.10f)
            .playIntervalSec(0.71f)
            .playCount(-1)
            .create();
    }

    // �����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move, FighterEnemyState::Run });
    {
        // �O���ɐi�ރR���|�[�l���g�i�����ԁj
        gameObject->createComponent<Act3D_MoveForward>(1.5f);

        // ���胂�[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyRun).lerpTimeSec(0.5f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerRun)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.55f)
            .playIntervalSec(0.39f)
            .playCount(-1)
            .create();
    }

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �U����Ԃ̐ݒ���s��
inline void setFighterEnemyAttackState(tktk::GameObjectPtr gameObject)
{
    // �W�����v�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::JumpAttack });
    {
        // �W�����v�U���ɂ��ړ��̃R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyJampAttackMoving>(4.5f, 0.5f, 4.0f, 1.8f);

        // �R�b��ɃW�����v�U�����������ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_FighterEnemyEndAttack>(3.0f, FighterEnemyState::JumpAttack);

        // �W�����v�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.2f, 2.8f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(2.0f, 1.0f, 2.0f));

        // �W�����v�A�^�b�N���[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyJumpAttack).isLoop(false).lerpTimeSec(0.5f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyJumpAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.5f)
            .playCount(1)
            .create();

        // ���k����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::red)
            .shrinkTargetPos({ 0.0f, 1.0f, 0.0f })
            .totalGenerateNum(30)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.5f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(1.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(30)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.6f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();
    }

    // �p���`�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::Punch });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(40.0f);

        // �P�b��Ƀp���`����X���C�v�Ɉڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_FighterEnemyStartComboAttack>();

         // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_FighterEnemyDamager>();
    
        // �p���`�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(0.2f, 0.8f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // �p���`���[�V�������J�n����
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyPunch).isLoop(false).lerpTimeSec(0.5f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyAttack1)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.4f)
            .playCount(1)
            .create();
    }

    // �X���C�v�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack, FighterEnemyState::Swiping });
    {
        // �v���C���[�̕��֌����R���|�[�l���g
        gameObject->createComponent<Act3D_RotateToPlayer>(40.0f);

        // �Q�b��ɃX���C�v���������ԂɈڍs���鏈����ݒ肷��
        gameObject->createComponent<Act3D_FighterEnemyEndAttack>(2.0f, FighterEnemyState::Swiping);

        // �G�l�~�[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_FighterEnemyDamager>();

        // �X���C�v�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_EnemyAttackRangeGenerator>(1.2f, 1.8f, tktkMath::Vector3(0.0f, 1.0f, 1.0f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // �X���C�v���[�V�������J�n����
        tktk::MotionChangerMaker::makeStart( gameObject).initMotionId(MotionId::FighterEnemySwiping).isLoop(false).lerpTimeSec(0.5f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyAttack2)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavyBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.4f)
            .playCount(1)
            .create();
    }

    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �ʏ��Ԃ̐ݒ���s��
inline void setFighterEnemyNormalState(tktk::GameObjectPtr gameObject)
{
    // �ҋ@��Ԃ̐ݒ���s��
    setFighterEnemyIdleState(gameObject);

    // �ړ���Ԃ̐ݒ���s��
    setFighterEnemyMoveState(gameObject);

    // �U����Ԃ̐ݒ���s��
    setFighterEnemyAttackState(gameObject);
}

// �_���[�W��Ԃ̐ݒ���s��
inline void setFighterEnemyDamageState(tktk::GameObjectPtr gameObject)
{
    // �_���[�W��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive, FighterEnemyState::Damage });
    {
        // �_���[�W�X�e�[�g���I�����鏈��
        gameObject->createComponent<Act3D_FighterEnemyEndDamage>();

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

        // �_���[�W���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyDamage).initFrame(5.0f).lerpTimeSec(0.1f).isLoop(false).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::FighterEnemyDamage)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// ������Ԃ̐ݒ���s��
inline void setFighterEnemyAliveState(tktk::GameObjectPtr gameObject)
{
    // ������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Alive });
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
        gameObject->createComponent<Act3D_GravityMove>();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});

    // �ʏ��Ԃ̐ݒ���s��
    setFighterEnemyNormalState(gameObject);

    // �_���[�W��Ԃ̐ݒ���s��
    setFighterEnemyDamageState(gameObject);
}

// ���S��Ԃ̐ݒ���s��
inline void setFighterEnemyDeadState(tktk::GameObjectPtr gameObject)
{
    // ���S��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ FighterEnemyState::Dead });
    {
        // ���S���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::FighterEnemyDead).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();
    
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
            .generateLocalPos({ 0.0f, 0.5f, -1.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .billboardScale({ 0.3f, 0.3f })
            .moveSpeedPerSec(1.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(30)
            .firstGenerateTimeSec(1.2f)
            .generateIntervalTimeSec(0.01f)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.0f, -1.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.2f)
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
        gameObject->createComponent<Act3D_EnemyDeleteTimer>();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_FighterEnemy::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // �G�l�~�[�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam initParam{};

    // �匳�̃X�e�[�g�́u�����v���u���S�v�̂ǂ��炩
    initParam.initRootNode({ FighterEnemyState::Alive, FighterEnemyState::Dead });

    // �u�����X�e�[�g�v�́u�ʏ�v�Ɓu�_���[�W�v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ FighterEnemyState::Alive }, { FighterEnemyState::Normal, FighterEnemyState::Damage });

    // �u�����E�ʏ�X�e�[�g�v�ɂ́u�ҋ@�v�u�ړ��v�u�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal },
        { FighterEnemyState::Idle, FighterEnemyState::Move, FighterEnemyState::Attack });

    // �u�����E�ʏ�E�ړ��X�e�[�g�v�ɂ́u�����v�u����v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Move },
        { FighterEnemyState::Walk,  FighterEnemyState::Run });

    // �u�����E�ʏ�E�U���X�e�[�g�v�ɂ́u�p���`�v�u�X���C�v�v�u�W�����v�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Attack },
        { FighterEnemyState::Punch, FighterEnemyState::Swiping, FighterEnemyState::JumpAttack });

    // �X�e�[�g�}�V���̏�����
    gameObject->setupStateMachine(initParam);

    // �ŏ��́u�����E�ʏ�E�ҋ@�X�e�[�g�v
    gameObject->statesEnable({ FighterEnemyState::Alive, FighterEnemyState::Normal, FighterEnemyState::Idle });

    // ������Ԃ̐ݒ���s��
    setFighterEnemyAliveState(gameObject);

    // ���S��Ԃ̐ݒ���s��
    setFighterEnemyDeadState(gameObject);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::FighterEnemy)
        .skeletonId(SkeletonId::FighterEnemy)
        .baseScale(0.1f)
        .baseRotation(tktkMath::Quaternion::createFromEulerAngle({ 0.0f, 180.0f, 0.0f }))
        .create();

    // ���b�V���̃A�j���[�V�����R���|�[�l���g
    tktk::MeshAnimatorMaker::makeStart(gameObject)
        .initMotionId(MotionId::FighterEnemyIdle)
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
    gameObject->createComponent<Act3D_FighterEnemyParam>();

    return gameObject;
}