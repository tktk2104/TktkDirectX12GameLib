#include "Sht2D_EnemyNormalBullet.h"

#include "../../../../Enums/Enums.h"
#include "Scripts//Sht2D_EnemyNormalBulletCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

tktk::GameObjectPtr Sht2D_EnemyNormalBullet::create(const tktkMath::Vector2& position, float rotate, const tktkMath::Vector2& velocity)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �G�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(tktkMath::Vector2(0.2f, 0.2f))
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .initVelocity(velocity)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::PlayerNormalBullet)
        .blendRate(tktkMath::Color_v::red)
        .create();

    // �����`�̏Փ˔���R���|�[�l���g
    tktk::RectColliderMaker::makeStart(gameObject)
        .rectSize(tktkMath::Vector2(32.0f, 64.0f))
        .collisionGroupType(CollisionGroup::EnemyBullet)
        .create();

#ifdef _DEBUG

    // �Փ˔���̋��E����`�悷��R���|�[�l���g
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();

#endif // _DEBUG

    // �ڐG���̃_���[�W�i�ڐG�J�n���_���[�W�A���b�̐ڐG���_���[�W�j
    gameObject->createComponent<Sht2D_DamagePower>(10.0f, 0.0f);

    // ��ʊO�ɏo���玩�g���E���R���|�[�l���g�i��ʔ͈͂̍�����W�A��ʔ͈͂̉E�����W�j
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // �G�l�~�[�ʏ�e�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_EnemyNormalBulletCollisionReaction>();

    return gameObject;
}
