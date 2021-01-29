#include "Sht2D_PlayerExplosionDamageRange.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerExplosionDamageRangeScript.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

tktk::GameObjectPtr Sht2D_PlayerExplosionDamageRange::create(const tktkMath::Vector2& position, const tktkMath::Vector2& scale, float effectIntervalTimeSec, float deleteTime, float startHitPower, float stayHitPowerPerSec)
{
    // �Q�[���I�u�W�F�N�g�����
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // �Q�[���v���C�V�[�����I���Ə�����I�u�W�F�N�g��\���^�O
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // �v���C���[�̍U���͈͂ł��邱�Ƃ�\���^�O
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // �񎟌����W�Ǘ��R���|�[�l���g
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(scale)
        .create();

    // �~�̏Փ˔���R���|�[�l���g
    tktk::CircleColliderMaker::makeStart(gameObject)
        .radius(32.0f)
        .collisionGroupType(CollisionGroup::PlayerBullet)
        .create();

    // �X�v���C�g�`��R���|�[�l���g
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Explosion)
        .create();

    // �X�v���C�g�A�j���[�V�����R���|�[�l���g
    tktk::SpriteAnimatorMaker::makeStart(gameObject)
        .totalAnimFrameSize(15U)
        .isLoop(false)
        .create();

    // �����̃X�v���C�g�A�j���[�V�����𕡐���������R���|�[�l���g
    tktk::SpriteSpreadEffectCreatorMaker::makeStart(gameObject)
        .generateLocalPosRandomRange(tktkMath::Vector2(24.0f, 24.0f))
        .generateIntervalTimeSec(effectIntervalTimeSec)
        .generateNumPerOnce(1)
        .spriteMaterialId(SpriteId::Explosion)
        .spriteScale(scale / 4.0f)
        .lifeTimeSec(1.0f)
        .moveSpeedPerSec(0.0f)
        .useAnimation(true)
        .totalAnimFrameSize(15U)
        .animSpeedRate(1.4f)
        .isLoop(false)
        .create();

#ifdef _DEBUG

    // �Փ˔���̋��E����`�悷��R���|�[�l���g
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();

#endif // _DEBUG

    // �ڐG���̃_���[�W
    gameObject->createComponent<Sht2D_DamagePower>(startHitPower, stayHitPowerPerSec);

    // ��莞�Ԍ�Ɏ��g���E���R���|�[�l���g
    gameObject->createComponent<Sht2D_PlayerExplosionDamageRangeScript>(deleteTime);

    return gameObject;
}
