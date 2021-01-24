#include "Sht2D_PlayerMissile.h"

#include "../../../../Enums/Enums.h"
#include "Scrits/Sht2D_PlayerMissileActiveTimer.h"
#include "Scrits/Sht2D_PlayerMissileCollisionReaction.h"
#include "Scrits/Sht2D_PlayerMissileExplode.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/RoteteToObject/Sht2D_RoteteToObject.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"
#include "../../Effects/Flame/Sht2D_Flame.h"

namespace
{
    // �ҋ@�X�e�[�g�̏���������
    inline void setupIdleState(tktk::GameObjectPtr gameObject, float activeTimeSec, const tktk::GameObjectPtr& lockOnTarget)
    {
        //  �ҋ@�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerMissileStateType::Idle });
        {
            gameObject->createComponent<Sht2D_PlayerMissileActiveTimer>(activeTimeSec);

            if (!lockOnTarget.expired())
            {
                gameObject->createComponent<Sht2D_RoteteToObject>(
                    360.0f,
                    lockOnTarget
                    );
            }
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // �A�N�e�B�u�X�e�[�g�̏���������
    inline void setupActiveState(tktk::GameObjectPtr gameObject, float moveSpeedPerSec, float accelerationPerSec, const tktk::GameObjectPtr& lockOnTarget)
    {
        //  �A�N�e�B�u�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerMissileStateType::Active });
        {
            // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
            gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, accelerationPerSec);
        
            // ���G�t�F�N�g�I�u�W�F�N�g�����g�̎q�v�f��
            gameObject->addChild(Sht2D_Flame::create({ 0.0f, 34.0f }, 180.0f));

            if (!lockOnTarget.expired())
            {
                gameObject->createComponent<Sht2D_RoteteToObject>(
                    90.0f,
                    lockOnTarget
                    );
            }
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_PlayerMissile::create(const tktkMath::Vector2& position, const tktkMath::Vector2& initVelocity, float rotate, float moveSpeedPerSec, float accelerationPerSec, float activeTimeSec, const tktk::GameObjectPtr& lockOnTarget)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};

    // �匳�̃X�e�[�g�́u�ҋ@�v�Ɓu�A�N�e�B�u�v�̂ǂ��炩
    stateInitParam.initRootNode({ PlayerMissileStateType::Idle, PlayerMissileStateType::Active });

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);

    // �ŏ��͑ҋ@�X�e�[�g
    gameObject->statesEnable({ PlayerMissileStateType::Idle });

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .initVelocity(initVelocity)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Missile)
        .create();

    // �����`�̏Փ˔���R���|�[�l���g
    tktk::RectColliderMaker::makeStart(gameObject)
        .rectSize({ 32.0f, 64.0f })
        .collisionGroupType(CollisionGroup::PlayerBullet)
        .create();

#ifdef _DEBUG

    // �Փ˔���̋��E����`�悷��R���|�[�l���g
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();

#endif // _DEBUG

    // �ڐG���̃_���[�W
    gameObject->createComponent<Sht2D_DamagePower>(30.0f, 0.0f);

    // ��ʊO�ɏo���玩�g���E���R���|�[�l���g
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f)
        );

    // �N���p�R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerMissileExplode>(60.0f, 200.0f);

    // �v���C���[�~�T�C���̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerMissileCollisionReaction>();

    // �ҋ@�X�e�[�g�̏���������
    setupIdleState(gameObject, activeTimeSec, lockOnTarget);

    // �A�N�e�B�u�X�e�[�g�̏���������
    setupActiveState(gameObject, moveSpeedPerSec, accelerationPerSec, lockOnTarget);

    return gameObject;
}
