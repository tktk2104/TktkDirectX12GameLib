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

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����Ɏ�������Ă���֐��̓v���C���[�̃X�e�[�g�p�^�[���̐ݒ�֐��ł��B
    ���@�X�e�[�g�p�^�[���̉�������Ă���������������̂ŁA�g�s�ځh�܂ŃX�N���[�����ĉ�����
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

namespace
{
    // �����X�e�[�g�̏���������
    inline void setupAliveState(tktk::GameObjectPtr gameObject)
    {
      /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
        ������̃X�e�[�g�ɑ�����R���|�[�l���g��q�v�f��ǉ��������ꍇ�́A�ugameObject->setTargetHierarchy(stateType)�v���g���ĉ������B
        ���@������x�����֐����ĂԂ܂Œǉ�����R���|�[�l���g��q�v�f���w�肵���X�e�[�g�ɑ�����悤�ɂȂ�܂��B
        ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

        //  �����X�e�[�g�ɒǉ�����ݒ���s��
        gameObject->setTargetHierarchy({ PlayerStateType::Alive });
        {
          /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
            ���uRectColliderMaker�v���g�����ƂŁuRectCollider�v�̃R���|�[�l���g����鎖���ł��܂��B
            ���@�uRectCollider�v�R���|�[�l���g�͒����`�̏Փ˔�����s���R���|�[�l���g�ł��B
            ���@�Փ˔���R���|�[�l���g�͑��ɂ��~�̏Փ˔�����s���uCircleCollider�v��A���p�`�|���S���̏Փ˔�����s���uPolygon2dCollider�v������܂��B
            ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

            // �����`�̏Փ˔���R���|�[�l���g
            tktk::RectColliderMaker::makeStart(gameObject)
                .rectSize(tktkMath::Vector2(32.0f, 88.0f))
                .collisionGroupType(CollisionGroup::Player)
                .create();

            /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
              ���uColliderWireFrameDrawer2DMaker�v���g�����ƂŁuColliderWireFrameDrawer2D�v�̃R���|�[�l���g����鎖���ł��܂��B
              ���@�uColliderWireFrameDrawer2D�v�R���|�[�l���g�͂Q�����̏Փ˔�����s���R���|�[�l���g�̔���͈̔͂�`�悷��R���|�[�l���g�ł��B
              ���@�����ۂ̃Q�[���ł͕K�v�̖����`�揈���Ȃ̂ŏ����R���p�C���Ńf�o�b�N�r���h�̂ݓK�����Ă��܂��B
              ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
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
            gameObject->addChild(Sht2D_Flame::create(tktkMath::Vector2(0.0f, 34.0f), 180.0f));
        }


      /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
        ������̃X�e�[�g�ɃR���|�[�l���g��q�v�f��ǉ������Ԃ��������������́A�ugameObject->setTargetHierarchy({})�v���g���ĉ������B
        ���@�������ɋ�̔z��i���m�ɂ͏������q���X�g�j��n���ƃX�e�[�g���������ɂȂ�܂��B
        ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

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


          /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
            ���uSpriteSpreadEffectCreatorMaker�v���g�����ƂŁuSpriteSpreadEffectCreator�v�̃R���|�[�l���g����鎖���ł��܂��B
            ���@�uSpriteSpreadEffectCreator�v�R���|�[�l���g�͊g�U����X�v���C�g�G�t�F�N�g�𐶐�����R���|�[�l���g�ł��B
            ���@�ƂĂ���ʂ̃p�����[�^�[�����݂���̂ŁA�uSpriteSpreadEffectCreatorMaker�v�Ɏ�������Ă���֐����Q�Ƃ��ĉ������B
            ���@���Z��R���|�[�l���g�Ƃ��āuSpriteShrinkEffectCreator�v�����݂��܂��B����́g���k����X�v���C�g�G�t�F�N�g�h�𐶐����镨�ł��B
            ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/
            
            // �팂�Ẳ��̃R���|�[�l���g
            tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
                .spriteMaterialId(SpriteId::Spark)
                .generateLocalPosRandomRange(tktkMath::Vector2(48.0f, 48.0f))
                .generateIntervalTimeSec(0.1f)
                .generateNumPerOnce(1)
                .totalGenerateNum(-1)
                .spriteBlendRate(tktkMath::Color(0.2f, 0.6f))
                .setChild(false)
                .lifeTimeSec(1.0f)
                .moveSpeedPerSec(1024.0f)
                .spriteScale(0.6f)
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

tktk::GameObjectPtr Sht2D_Player::create(const tktkMath::Vector2& position)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::Player);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����̃t���[�����[�N�̃Q�[���I�u�W�F�N�g�́g�X�e�[�g�}�V���h�Ƃ����@�\�������Ă��܂��B
    ���@���̋@�\���g���ׂ̏����ݒ�����̍s�ōs���Ă��܂��B
    ���@�g�X�e�[�g�}�V���h�Ƃ́g�X�e�[�g�p�^�[���h�ŏ������������鎞�̏����ƂȂ�@�\�ł��B
    ���@�g�X�e�[�g�p�^�[���h�Ƃ́A�����̏�Ԃ��`���A���̏�Ԃɂ���ėL���ɂ���R���|�[�l���g��ω���������̂ł��B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �X�e�[�g�}�V�����g�p���鏀�����s��
    tktk::StateMachineListInitParam stateInitParam{};


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ���utktk::StateMachineListInitParam�v�̍\���̂��g�p���ď��������s���܂��B
    ���@���̍\���̂ɂ͐ݒ�p�֐����������݂��A���̂P�ɁustateMachineListInitParam.initRootNode(rootState)�v������܂��B
    ���@���̊֐��ł͑匳�̃X�e�[�g�̎�ނ�ݒ肵�܂��B
    ���@�uPlayerStateType�v�͎����ō��񋓌^�ł��B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �匳�̃X�e�[�g�́u�����v�Ɓu���S�v�̂ǂ��炩
    stateInitParam.initRootNode({ PlayerStateType::Alive, PlayerStateType::Dead });


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ���ugameObject->setupStateMachine(stateMachineListInitParam)�v���ĂԂ��ƂŃX�e�[�g�}�V���̏��������������܂��B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �X�e�[�g�}�V���̏��������s��
    gameObject->setupStateMachine(stateInitParam);


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    ������̃X�e�[�g��L���ɂ���ɂ́ugameObject->stateEnable(PlayerStateType::Alive)�v���g���ĉ������B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �ŏ��͐����X�e�[�g
    gameObject->stateEnable(PlayerStateType::Alive);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .create();

  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���uInertialMovement2DMaker�v���g�����ƂŁuInertialMovement2D�v�̃R���|�[�l���g����鎖���ł��܂��B
    ���@�uInertialMovement2D�v�R���|�[�l���g�͂Q���������ړ����s���R���|�[�l���g�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(1024.0f)
        .create();


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	���uSpriteDrawerMaker�v���g�����ƂŁuSpriteDrawer�v�̃R���|�[�l���g����鎖���ł��܂��B
    ���@�uSpriteDrawer�v�R���|�[�l���g�͓ǂݍ��񂾃e�N�X�`����`�悷��R���|�[�l���g�ł��B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Player)
        .create();

    // �ڐG���̃_���[�W�p���[�R���|�[�l���g�i�ڐG�J�n���_���[�W�A���b�̐ڐG���_���[�W�j
    gameObject->createComponent<Sht2D_DamagePower>(0.0f, 20.0f);

    // �v���C���[�ϋv�͂̃R���|�[�l���g�i�ő�ϋv�́j
    gameObject->createComponent<Sht2D_HealthPoint>(100.0f);

    // �v���C���[�e���R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerBulletCount>();


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����́uSht2D_PlayerCollisionReaction�v���V���O���N���b�N��F12�L�[����͂��ă\�[�X�t�@�C���ɔ��ŉ������B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �v���C���[�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerCollisionReaction>();


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����́usetupAliveState(...)�v���V���O���N���b�N��F12�L�[����͂��Ċ֐��̎����ɔ��ŉ������B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // �����X�e�[�g�̏���������
    setupAliveState(gameObject);


  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
    �����́usetupDeadState(...)�v���V���O���N���b�N��F12�L�[����͂��Ċ֐��̎����ɔ��ŉ������B
    ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

    // ���S�X�e�[�g�̏���������
    setupDeadState(gameObject);

    return gameObject;
}