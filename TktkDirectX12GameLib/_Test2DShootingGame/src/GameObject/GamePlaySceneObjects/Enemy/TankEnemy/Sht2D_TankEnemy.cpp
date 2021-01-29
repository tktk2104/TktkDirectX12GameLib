#include "Sht2D_TankEnemy.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_TankEnemyDamager.h"
#include "Scripts/Sht2D_TankEnemyTopRotator.h"
#include "Scripts/Sht2D_TankEnemyNormalBulletCreator.h"
#include "../_CommonEnemyScripts/CollisionReaction/Sht2D_EnemyCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/HealthPoint/Sht2D_HealthPoint.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
    // �C��̃I�u�W�F�N�g
    inline tktk::GameObjectPtr createTop()
    {
        // �Q�[���I�u�W�F�N�g�����
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // �񎟌����W�Ǘ��R���|�[�l���g
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // �X�v���C�g�`��R���|�[�l���g
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::TankEnemyTop)
            .create();

        // ��ԃG�l�~�[�̖C���̉�]�R���|�[�l���g
        gameObject->createComponent<Sht2D_TankEnemyTopRotator>();

        // ��ԃG�l�~�[�̒e���˃R���|�[�l���g
        gameObject->createComponent<Sht2D_TankEnemyNormalBulletCreator>();

        return gameObject;
    }

    // �����X�e�[�g�̏���������
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ TankEnemyStateTypes::Alive });
        {
            // �����`�̏Փ˔���R���|�[�l���g
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize(tktkMath::Vector2(96.0f, 128.0f))
                .collisionGroupType(CollisionGroup::Enemy)
                .create();

#ifdef _DEBUG
            // �Փ˔���̋��E����`�悷��R���|�[�l���g
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::red)
                .create();
#endif // _DEBUG

            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(100.0f, 4096.0f);

            // ��ԃG�l�~�[�̃_���[�W�����R���|�[�l���g
            gameObject->createComponent<Sht2D_TankEnemyDamager>();

            // ��Ԃ̖C������g�̎q���ɂ���
            gameObject->addChild(createTop());
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // ���S�X�e�[�g�̏���������
    inline void setupDeadState(tktk::GameObjectPtr gameObject)
    {
        //  ���S�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ TankEnemyStateTypes::Dead });
        {
            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(700.0f, 1124.0f);

            // �팂�Ẳ��̃R���|�[�l���g
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange(tktkMath::Vector2(48.0f, 48.0f))
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate(tktkMath::Color(1.0f, 0.5f))
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(tktkMath::Vector2(0.6f, 0.6f))
                .spriteBlendRate(tktkMath::Color(0.2f, 0.6f))
                .minGenerateAngleDeg(170.0f)
                .maxGenerateAngleDeg(190.0f)
                .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -1.0f))
                .create();

            // �����̃X�v���C�g�A�j���[�V�����𕡐���������R���|�[�l���g
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .generateLocalPosRandomRange(tktkMath::Vector2(128.0f, 128.0f))
                .generateIntervalTimeSec(0.2f)
                .generateNumPerOnce(1)
                .totalGenerateNum(10)
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

tktk::GameObjectPtr Sht2D_TankEnemy::create(const tktkMath::Vector2& position, float rotate)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �G�ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::Enemy);

    // �G�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};

    // �匳�̃X�e�[�g�́u�����v�Ɓu���S�v�̂ǂ��炩
    stateInitParam.initRootNode({ TankEnemyStateTypes::Alive, TankEnemyStateTypes::Dead });

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);

    // �ŏ��͐����X�e�[�g
    gameObject->statesEnable({ TankEnemyStateTypes::Alive });

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::TankEnemyBase)
        .create();

    // �L���^�s������o�鉌�̃R���|�[�l���g�i���j
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Spark)
        .generateLocalPos(tktkMath::Vector2(48.0f, -48.0f))
        .generateIntervalTimeSec(0.1f)
        .generateNumPerOnce(1)
        .totalGenerateNum(-1)
        .setChild(false)
        .lifeTimeSec(4.0f)
        .moveSpeedPerSec(1024.0f)
        .spriteScale(tktkMath::Vector2(0.4f, 0.4f))
        .spriteBlendRate(tktkMath::Color(1.0f, 0.1f))
        .minGenerateAngleDeg(170.0f)
        .maxGenerateAngleDeg(190.0f)
        .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -0.1f))
        .create();

    // �L���^�s������o�鉌�̃R���|�[�l���g�i�E�j
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Spark)
        .generateLocalPos(tktkMath::Vector2(-48.0f, -48.0f))
        .generateIntervalTimeSec(0.1f)
        .generateNumPerOnce(1)
        .totalGenerateNum(-1)
        .setChild(false)
        .lifeTimeSec(4.0f)
        .moveSpeedPerSec(1024.0f)
        .spriteScale(tktkMath::Vector2(0.4f, 0.4f))
        .spriteBlendRate(tktkMath::Color(1.0f, 0.1f))
        .minGenerateAngleDeg(170.0f)
        .maxGenerateAngleDeg(190.0f)
        .blendRateChangeWidthPerSec(tktkMath::Color(0.0f, -0.1f))
        .create();

    // �ڐG���̃_���[�W�i�ڐG�J�n���_���[�W�A���b�̐ڐG���_���[�W�j
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 10.0f);

    // ��ԃG�l�~�[�ϋv�͂̃R���|�[�l���g�i�ő�ϋv�́j
    gameObject->createComponent<Sht2D_HealthPoint>(90.0f);

    // �G�l�~�[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_EnemyCollisionReaction>();

    // ��ʊO�ɏo���玩�g���E���R���|�[�l���g�i��ʔ͈͂̍�����W�A��ʔ͈͂̉E�����W�j
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // �����X�e�[�g�̏���������
    setupAliveState(gameObject);

    // ���S�X�e�[�g�̏���������
    setupDeadState(gameObject);

    return gameObject;
}