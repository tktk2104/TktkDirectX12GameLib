#include "Sht2D_PlayerBomb.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerBombActiveTimer.h"
#include "Scripts/Sht2D_PlayerBombCollisionReaction.h"
#include "Scripts/Sht2D_PlayerBombExplode.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

namespace
{
    // �ҋ@�X�e�[�g�̏���������i�v���C���[�{���I�u�W�F�N�g�A�{���N�����ԁj
    inline void setupIdleState(tktk::GameObjectPtr gameObject, float activeTimeSec)
    {
        //  �ҋ@�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerBombStateType::Idle });
        {
            // �X�v���C�g�`��R���|�[�l���g
            tktk::SpriteDrawerMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::BompCore)
                .blendRate(tktkMath::Color_v::red)
                .create();

            // �v���C���[�{���̃A�N�e�B�u�^�C�}�[�R���|�[�l���g�i�{���N�����ԁj
            gameObject->createComponent<Sht2D_PlayerBombActiveTimer>(activeTimeSec);
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }

    // �A�N�e�B�u�X�e�[�g�̏���������
    inline void setupActiveState(tktk::GameObjectPtr gameObject)
    {
        //  �A�N�e�B�u�X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerBombStateType::Active });
        {
            // �X�v���C�g�`��R���|�[�l���g
            tktk::SpriteDrawerMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::BompCore)
                .blendRate(tktkMath::Color_v::blue)
                .create();

            // �~�̏Փ˔���R���|�[�l���g
            tktk::CircleColliderMaker::makeStart(gameObject)
                .radius(16.0f)
                .collisionGroupType(CollisionGroup::PlayerBullet)
                .create();

#ifdef _DEBUG

            // �Փ˔���̋��E����`�悷��R���|�[�l���g
            tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
                .lineColor(tktkMath::Color_v::blue)
                .create();

#endif // _DEBUG

            // �v���C���[�{���̏Փ˔��胊�A�N�V�����R���|�[�l���g
            gameObject->createComponent<Sht2D_PlayerBombCollisionReaction>();
        }
        // ����̏�Ԃɒǉ�����ݒ����������
        gameObject->setTargetHierarchy({ });
    }
}

tktk::GameObjectPtr Sht2D_PlayerBomb::create(const tktkMath::Vector2& position, float rotate, float moveSpeedPerSec, float activeTimeSec)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};

    // �匳�̃X�e�[�g�́u�ҋ@�v�Ɓu�A�N�e�B�u�v�̂ǂ��炩
    stateInitParam.initRootNode({ PlayerBombStateType::Idle, PlayerBombStateType::Active });

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);

    // �ŏ��͑ҋ@�X�e�[�g
    gameObject->statesEnable({ PlayerBombStateType::Idle });

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(tktkMath::Vector2(0.5f, 0.5f))
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::BompFrame)
        .create();

    // �ڐG���̃_���[�W�i�ڐG�J�n���_���[�W�A���b�̐ڐG���_���[�W�j
    gameObject->createComponent<Sht2D_DamagePower>(30.0f, 0.0f);

    // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
    gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, std::numeric_limits<float>::max());

    // ��ʊO�ɏo���玩�g���E���R���|�[�l���g
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // �N���p�R���|�[�l���g�i�ڐG�J�n���_���[�W�A���b�̐ڐG���_���[�W�j
    gameObject->createComponent<Sht2D_PlayerBombExplode>(200.0f, 500.0f);

    // �ҋ@�X�e�[�g�̏���������i�v���C���[�{���I�u�W�F�N�g�A�{���N�����ԁj
    setupIdleState(gameObject, activeTimeSec);

    // �A�N�e�B�u�X�e�[�g�̏���������
    setupActiveState(gameObject);

    return gameObject;
}