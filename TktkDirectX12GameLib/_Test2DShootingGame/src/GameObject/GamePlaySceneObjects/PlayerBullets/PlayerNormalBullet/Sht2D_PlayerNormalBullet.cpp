#include "Sht2D_PlayerNormalBullet.h"

#include <limits>
#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerNormalBulletCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/MoveForward/Sht2D_MoveForward.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

tktk::GameObjectPtr Sht2D_PlayerNormalBullet::create(const tktkMath::Vector2& position, float rotate, float moveSpeedPerSec)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(0.2f)
        .create();

    // �񎟌������ړ��R���|�[�l���g
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::PlayerNormalBullet)
        .blendRate(tktkMath::Color_v::blue)
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

    // �O���Ɉړ�����R���|�[�l���g�i���b�ړ����x, ���b�������x�j
    gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, std::numeric_limits<float>::max());

    // ��ʊO�ɏo���玩�g���E���R���|�[�l���g
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f)
        );

    // �v���C���[�ʏ�e�̏Փ˔��胊�A�N�V�����R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerNormalBulletCollisionReaction>();

    return gameObject;
}
