#include "Act3D_Player.h"

#include "../../../../Enums/Enums.h"

#include "Scripts/Act3D_PlayerController.h"
#include "Scripts/Act3D_InputToStartAttack.h"
#include "Scripts/Act3D_InputToStartComboAttack.h"
#include "Scripts/Act3D_InputToStartDodge.h"
#include "Scripts/Act3D_JampAttackMoving.h"
#include "Scripts/Act3D_PlayerAttackRangeGenerator.h"
#include "Scripts/Act3D_PlayerCollisionReaction.h"
#include "Scripts/Act3D_PlayerDamager.h"
#include "Scripts/Act3D_PlayerEndAttack.h"
#include "Scripts/Act3D_PlayerEndDodge.h"
#include "Scripts/Act3D_PlayerEndDamage.h"
#include "Scripts/Act3D_PlayerParam.h"

#include "../../../_CommonScripts/GravityMove/Act3D_GravityMove.h"

#include "../../../SkyBox/Act3D_SkyBox.h"

// �ړ���Ԃ̐ݒ���s��
inline void setPlayerMoveState(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move });
    {
        // �v���C���[�ړ����A�ړ��X�e�[�g�ύX�R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerController>(2.0f, 75.0f);

        // �U���J�n���s���R���|�[�l���g
        gameObject->createComponent<Act3D_InputToStartAttack>();

        // ����J�n���s���R���|�[�l���g
        gameObject->createComponent<Act3D_InputToStartDodge>();

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();
    }

    // �ҋ@��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::Idle });
    {
        // �ҋ@���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerIdle).lerpTimeSec(0.3f).create();
    }

    // �O��������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkForward });
    {
        // �O�������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkForward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.28f)
            .playCount(-1)
            .create();
    }

    // ���������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkBackward });
    {
        // ��������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkBackward).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.31f)
            .playCount(-1)
            .create();
    }

    // ��������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal,  PlayerStateType::Move, PlayerStateType::WalkLeft });
    {
        // �������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkLeft).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.26f)
            .playCount(-1)
            .create();
    }

    // �E������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::WalkRight });
    {
        // �E�����ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerWalkRight).lerpTimeSec(0.2f).motionSpeedRate(2.0f).create();
    
        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerWalk)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.15f)
            .playIntervalSec(0.27f)
            .playCount(-1)
            .create();
    }

    // �O�������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move, PlayerStateType::RunForward });
    {
        // �O������ړ����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerRunForward).lerpTimeSec(0.2f).motionSpeedRate(1.5f).create();
    
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
inline void setPlayerAttackState(tktk::GameObjectPtr gameObject)
{
    // �U���i�P�i�j��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack1 });
    {
        // �U���i�P�i�j�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.1f, 0.3f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(1.0f, 1.0f, 1.0f));

        // �P�i�ڂ���Q�i�ڂ̍U���ɑJ�ڂ���R���|�[�l���g
        gameObject->createComponent<Act3D_InputToStartComboAttack>();

        // �U���i�P�i�j���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack1).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(2.0f).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.5f);

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerAttack1)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightSword)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.1f)
            .playCount(1)
            .create();
    }

    // �U���i�Q�i�j��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::Attack2 });
    {
        // �U���i�Q�i�j�̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(0.2f, 0.5f, tktkMath::Vector3(0.0f, 1.0f, 0.6f), tktkMath::Vector3(2.0f, 1.0f, 1.0f));

        // �U���i�Q�i�j���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerAttack2).initFrame(15.0f).lerpTimeSec(0.1f).isLoop(false).motionSpeedRate(1.5f).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(0.8f);

        // �v���C���[�̃_���[�W�����R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerDamager>();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerAttack2)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::MiddleSword)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.2f)
            .playCount(1)
            .create();
    }

    // �W�����v�U����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack, PlayerStateType::JumpAttack });
    {
        // �W�����v�U���̍U���͈͂��o��������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerAttackRangeGenerator>(1.0f, 2.0f, tktkMath::Vector3(0.0f, 1.0f, 0.5f), tktkMath::Vector3(1.0f, 1.0f, 2.0f));

        // �W�����v�U���ɂ��ړ��̃R���|�[�l���g
        gameObject->createComponent<Act3D_JampAttackMoving>();

        // ���k����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardShrinkEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate(tktkMath::Color_v::blue)
            .shrinkTargetPos({ 0.0f, 1.0f, 0.0f })
            .totalGenerateNum(20)
            .setChild(true)
            .changeAvtiveToReset(true)
            .create();

        // �g�U����r���{�[�h�p�[�e�B�N���R���|�[�l���g
        tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
            .billboardMaterialId(BillBoardId::Spark)
            .billboardBlendRate({ 0.3f, 0.3f, 0.3f, 1.0f }) // �O���[
            .generateLocalPos({ 0.0f, 0.5f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .billboardScale({ 0.2f, 0.2f })
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
            .generateLocalPos({ 0.0f, 0.0f, 0.0f })
            .generateLocalPosRandomRange({ 0.2f, 0.2f, 0.2f })
            .moveSpeedPerSec(3.0f)
            .lifeTimeSec(0.6f)
            .generateNumPerOnce(10)
            .totalGenerateNum(60)
            .firstGenerateTimeSec(1.2f)
            .generateIntervalTimeSec(0.02f)
            .changeAvtiveToReset(true)
            .create();

        // �W�����v�U�����[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerJumpAttack).initFrame(20.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // �U���X�e�[�g���I������R���|�[�l���g
        gameObject->createComponent<Act3D_PlayerEndAttack>(2.0f);

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerJumpAttack)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::HeavySword)
            .startToPlay(false)
            .firstPlayStartTimeSec(1.0f)
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
inline void setPlayerNormalState(tktk::GameObjectPtr gameObject)
{
    // �ړ���Ԃ̐ݒ���s��
    setPlayerMoveState(gameObject);

    // �U����Ԃ̐ݒ���s��
    setPlayerAttackState(gameObject);
}

// �����Ԃ̐ݒ���s��
inline void setPlayerDodgeState(tktk::GameObjectPtr gameObject)
{
    // �����Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Dodge });
    {
        // ����X�e�[�g���I�����鏈��
        gameObject->createComponent<Act3D_PlayerEndDodge>();

        // ������[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDodge).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::LightBlow)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.5f)
            .playCount(1)
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
            .generateIntervalTimeSec(0.1f)
            .changeAvtiveToReset(true)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// �_���[�W��Ԃ̐ݒ���s��
inline void setPlayerDamageState(tktk::GameObjectPtr gameObject)
{
    // �_���[�W��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive, PlayerStateType::Damage });
    {
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
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDamage).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerDamage)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

// ������Ԃ̐ݒ���s��
inline void setPlayerAliveState(tktk::GameObjectPtr gameObject)
{
    // ������Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Alive });
    {
        // �R���������ړ��R���|�[�l���g
        tktk::InertialMovement3DMaker::makeStart(gameObject)
            .decelerationPerSec(2.0f)
            .craete();

        // OBB�Փ˔���R���|�[�l���g
        tktk::BoxColliderMaker::makeStart(gameObject)
            .boxSize({ 0.8f, 1.6f, 0.8f })
            .localPosition({ 0.0f, 0.8f, 0.0f })
            .collisionGroupType(CollisionGroup::Player)
            .isExtrude(true)
            .extrudedRate(1.0f)
            .create();

        // �v���C���[�̏Փ˔���̃��A�N�V����
        gameObject->createComponent<Act3D_PlayerCollisionReaction>();

        // �d�͂ɂ��ړ��R���|�[�l���g
        gameObject->createComponent<Act3D_GravityMove>();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});

    // �ʏ��Ԃ̐ݒ���s��
    setPlayerNormalState(gameObject);

    // �����Ԃ̐ݒ���s��
    setPlayerDodgeState(gameObject);

    // �_���[�W��Ԃ̐ݒ���s��
    setPlayerDamageState(gameObject);
}

// ���S��Ԃ̐ݒ���s��
inline void setPlayerDeadState(tktk::GameObjectPtr gameObject)
{
    // ���S��Ԃɒǉ�����ݒ���s��
    gameObject->setTargetHierarchy({ PlayerStateType::Dead });
    {
        // ���S���[�V�������s���R���|�[�l���g
        tktk::MotionChangerMaker::makeStart(gameObject).initMotionId(MotionId::PlayerDead).initFrame(10.0f).lerpTimeSec(0.1f).isLoop(false).create();

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

        // �T�E���h�Đ��^�C�}�[
        tktk::SoundPlayTimerMaker::makeStart(gameObject)
            .soundId(SoundId::PlayerDead)
            .startToPlay(false)
            .firstPlayStartTimeSec(0.0f)
            .playCount(1)
            .create();
    }
    // ����̏�Ԃɒǉ�����ݒ����������
    gameObject->setTargetHierarchy({});
}

tktk::GameObjectPtr Act3D_Player::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotation)
{
    // �Q�[���I�u�W�F�N�g���쐬
    auto gameObject = tktk::DX12Game::createGameObject();

    // ���C���V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // �v���C���[�^�O��ǉ�
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam initParam{};

    // �匳�̃X�e�[�g�́u�����v�Ɓu���S�v�̂ǂ��炩
    initParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });

    // �u�����X�e�[�g�v�́u�ʏ�v�Ɓu����v�u�_���[�W�v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ PlayerStateType::Alive }, { PlayerStateType::Normal, PlayerStateType::Dodge, PlayerStateType::Damage });

    // �u�����E�ʏ�X�e�[�g�v�́u�ړ��v�Ɓu�U���v�̂Q�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal }, { PlayerStateType::Move, PlayerStateType::Attack });

    // �u�����E�ʏ�E�ړ��X�e�[�g�v�́u�ҋ@�v�Ɓu�O������v�u�e���ʕ����v�X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move }, {
            PlayerStateType::Idle,
            PlayerStateType::WalkForward,
            PlayerStateType::WalkBackward,
            PlayerStateType::WalkLeft,
            PlayerStateType::WalkRight,
            PlayerStateType::RunForward
        });

    // �u�����E�ʏ�E�U���X�e�[�g�v�́u��i�ڍU���v�Ɓu��i�ڍU���v�u�W�����v�U���v�̂R�̃X�e�[�g���琬�藧���Ă���
    initParam.addChildNode({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Attack },{ PlayerStateType::Attack1, PlayerStateType::Attack2, PlayerStateType::JumpAttack });
    
    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(initParam);

    // �ŏ��͈ړ��X�e�[�g
    gameObject->statesEnable({ PlayerStateType::Alive, PlayerStateType::Normal, PlayerStateType::Move });

    // ������Ԃ̐ݒ���s��
    setPlayerAliveState(gameObject);

    // ���S��Ԃ̐ݒ���s��
    setPlayerDeadState(gameObject);

    // �R�������W�R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // ���b�V���`��R���|�[�l���g
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(MeshId::Player)
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

// �Փ˔���͈͕`��R���|�[�l���g
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();
#endif // _DEBUG

    // �v���C���[�̔\�͒l
    gameObject->createComponent<Act3D_PlayerParam>();

    // �J���������g�̎q���ɐݒ肷��
    gameObject->addChild(createCamera({ 0.0f, 3.0f, -3.0f }, tktkMath::Quaternion::createLookRotation({ 0.0f, -1.0f, 3.0f })));

    return gameObject;
}

tktk::GameObjectPtr Act3D_Player::createCamera(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �v���C���[�J�����^�O��t����
    gameObject->addGameObjectTag(GameObjectTag::PlayerCamera);

    // ���W�Ǘ��R���|�[�l���g
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(rotation)
        .create();

    // �ʏ�J�����R���|�[�l���g
    tktk::BasicCameraControllerMaker::makeStart(gameObject)
        .initCameraFov(90.0f)
        .create();

    // �V���h�E�}�b�v�J�����R���|�[�l���g
    tktk::ShadowMapCameraControllerMaker::makeStart(gameObject)
        .direction({ 0.0f, -1.0f, 1.0f })
        .initCameraWidth(50.0f)
        .initCameraHeight(50.0f)
        .initCameraNear(0.0f)
        .initCameraFar(100.0f)
        .targetTag(GameObjectTag::Player)
        .create();

    // �X�J�C�{�b�N�X�I�u�W�F�N�g���q�v�f�ɒǉ�����
    gameObject->addChild(Act3D_SkyBox::create());

    return gameObject;
}
