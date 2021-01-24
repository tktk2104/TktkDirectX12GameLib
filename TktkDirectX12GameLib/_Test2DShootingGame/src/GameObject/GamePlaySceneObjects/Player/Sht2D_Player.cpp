#include "Sht2D_Player.h"

#include "../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerBulletCount.h"
#include "Scripts/Sht2D_PlayerMoveScript.h"
#include "Scripts/Sht2D_PlayerNormalBulletCreator.h"
#include "Scripts/Sht2D_PlayerMissileCreator.h"
#include "Scripts/Sht2D_PlayerBombCreator.h"
#include "Scripts/Sht2D_PlayerCollisionReaction.h"
#include "Scripts/Sht2D_PlayerDamager.h"
#include "../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../Effects/Flame/Sht2D_Flame.h"

namespace
{
    // �����X�e�[�g�̏���������
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerStateType::Alive });
        {
            // �����`�̏Փ˔���R���|�[�l���g
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize({ 32.0f, 88.0f })
                .collisionGroupType(CollisionGroup::Player)
                .create();

#ifdef _DEBUG
            // �Փ˔���̋��E����`�悷��R���|�[�l���g
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::blue)
                .create();
#endif // _DEBUG

            // �v���C���[�ړ��R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerMoveScript>();

            // �v���C���[�ʏ�e���˃R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerNormalBulletCreator>();

            // �v���C���[�~�T�C�����˃R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerMissileCreator>();

            // �v���C���[�{�����˃R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerBombCreator>();

            // �v���C���[�̃_���[�W�����R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerDamager>();

            // ���G�t�F�N�g�I�u�W�F�N�g�����g�̎q�v�f��
            gameObject->addChild(Sht2D_Flame::create({ 0.0f, 34.0f }, 180.0f));
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // ���S�X�e�[�g�̏���������
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  ���S�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerStateType::Dead });
        {
            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(-700.0f, 1124.0f);

            // �팂�Ẳ��̃R���|�[�l���g
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange({ 48.0f, 48.0f })
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate({ 1.0f, 0.5f })
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(0.6f)
                .spriteBlendRate({ 0.2f, 0.6f })
                .minGenerateAngleDeg(170.0f)
                .maxGenerateAngleDeg(190.0f)
                .blendRateChangeWidthPerSec({ 0.0f, -1.0f })
                .create();

            // �����̃X�v���C�g�A�j���[�V�����𕡐���������R���|�[�l���g
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .generateLocalPosRandomRange({ 128.0f, 128.0f })
                .generateIntervalTimeSec(0.2f)
                .generateNumPerOnce(1)
                .totalGenerateNum(10U)
                .spriteMaterialId(SpriteId::Explosion)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(0.0f)
                .setChild(true)
                .useAnimation(true)
                .totalAnimFrameSize(15U)
                .animSpeedRate(1.4f)
                .isLoop(false)
                .create();
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_Player::create(const tktkMath::Vector2& position)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};

    // �匳�̃X�e�[�g�́u�����v�Ɓu���S�v�̂ǂ��炩
    stateInitParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);

    // �ŏ��͐����X�e�[�g
    gameObject->statesEnable({ PlayerStateType::Alive });

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Player)
        .create();

    // �ڐG���̃_���[�W
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 20.0f);

    // �v���C���[�ϋv�͂̃R���|�[�l���g
    gameObject->createComponent<Sht2D_HealthPoint>(100.0f);

    // �v���C���[�e���R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerBulletCount>();

    // �v���C���[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerCollisionReaction>();

    // �����X�e�[�g�̏���������
    setupAliveState(gameObject);

    // ���S�X�e�[�g�̏���������
    setupDeadState(gameObject);

    return gameObject;
}