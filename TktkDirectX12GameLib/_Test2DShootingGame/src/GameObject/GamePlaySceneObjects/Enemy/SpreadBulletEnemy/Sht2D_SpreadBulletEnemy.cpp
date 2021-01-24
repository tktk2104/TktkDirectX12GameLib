#include "Sht2D_SpreadBulletEnemy.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_DoubleSideMove.h"
#include "Scripts/Sht2D_SpreadBulletEnemyCombatStarter.h"
#include "Scripts/Sht2D_SpreadBulletEnemyDamager.h"
#include "Scripts/Sht2D_SpreadBulletEnemyBulletCreator.h"
#include "../_CommonEnemyScripts/CollisionReaction/Sht2D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/AutoRotater/Sht2D_AutoRotater.h"
#include "../../../_CommonScripts/GameClearMessageSender/Sht2D_GameClearMessageSender.h"

namespace
{
    // �`��p�I�u�W�F�N�g
    inline tktk::GameObjectPtr createSpriteObject()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // �񎟌����W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // �X�v���C�g�`��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::SpreadBulletEnemy)
            .create();

        // ������]�R���|�[�l���g
        gameObject->createComponent<Sht2D_AutoRotater>(720.0f);

        return gameObject;
    }

    // ����X�e�[�g�̏���������
    inline void setupEntryState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Entry });
        {
            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(150.0f, 4096.0f);
        
            gameObject->createComponent<Sht2D_SpreadBulletEnemyCombatStarter>();
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // �퓬�X�e�[�g�̏���������
    inline void setupCombatState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Combat });
        {
            gameObject->createComponent<Sht2D_SpreadBulletEnemyBulletCreator>();

            gameObject->createComponent<Sht2D_DoubleSideMove>(
                100.0f, 2048.0f,
                512.0f, tktk::DX12Game::getScreenSize().x - 512.0f
                );
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // �����X�e�[�g�̏���������
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Alive });
        {
            tktk::CircleColliderMaker::makeStart(gameObject)
                .radius(32.0f)
                .collisionGroupType(CollisionGroup::Enemy)
                .create();

            gameObject->createComponent<Sht2D_SpreadBulletEnemyDamager>();
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });

        // ����X�e�[�g�̏���������
        setupEntryState(gameObject);

        // �퓬�X�e�[�g�̏���������
        setupCombatState(gameObject);
    }

    // ���S�X�e�[�g�̏���������
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ SpreadBulletEnemyState::Dead });
        {
            // �Q�[�����N���A�������b�Z�[�W�𑗐M����R���|�[�l���g
            gameObject->createComponent<Sht2D_GameClearMessageSender>();

            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(700.0f, 1124.0f);

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

tktk::GameObjectPtr Sht2D_SpreadBulletEnemy::create(const tktkMath::Vector2& position, float rotate)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �G�ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // �{�X�ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::Boss);

    // �G�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};

    // �匳�̃X�e�[�g�́u�����v�Ɓu���S�v�̂ǂ��炩
    stateInitParam.initRootNode({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Dead });

    // �����X�e�[�g�́u����v�Ɓu�퓬�v�̂ǂ��炩
    stateInitParam.addChildNode({ SpreadBulletEnemyState::Alive }, { SpreadBulletEnemyState::Entry, SpreadBulletEnemyState::Combat });

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);

    // �ŏ��͐����A����X�e�[�g
    gameObject->statesEnable({ SpreadBulletEnemyState::Alive, SpreadBulletEnemyState::Entry });

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    gameObject->addChild(createSpriteObject());

    // �ڐG���̃_���[�W
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 10.0f);

    // �g�U�e�G�l�~�[�ϋv�͂̃R���|�[�l���g
    gameObject->createComponent<Sht2D_HealthPoint>(1000.0f);

    // �G�l�~�[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_EnemyCollisionReaction>();

    // �����X�e�[�g�̏���������
    setupAliveState(gameObject);

    // ���S�X�e�[�g�̏���������
    setupDeadState(gameObject);

    return gameObject;
}
