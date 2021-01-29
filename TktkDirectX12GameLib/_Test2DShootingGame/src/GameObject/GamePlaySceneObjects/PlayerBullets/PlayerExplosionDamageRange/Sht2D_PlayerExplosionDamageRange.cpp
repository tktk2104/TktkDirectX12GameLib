#include "Sht2D_PlayerExplosionDamageRange.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerExplosionDamageRangeScript.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"

tktk::GameObjectPtr Sht2D_PlayerExplosionDamageRange::create(const tktkMath::Vector2& position, const tktkMath::Vector2& scale, float effectIntervalTimeSec, float deleteTime, float startHitPower, float stayHitPowerPerSec)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(scale)
        .create();

    // 円の衝突判定コンポーネント
    tktk::CircleColliderMaker::makeStart(gameObject)
        .radius(32.0f)
        .collisionGroupType(CollisionGroup::PlayerBullet)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Explosion)
        .create();

    // スプライトアニメーションコンポーネント
    tktk::SpriteAnimatorMaker::makeStart(gameObject)
        .totalAnimFrameSize(15U)
        .isLoop(false)
        .create();

    // 爆発のスプライトアニメーションを複数生成するコンポーネント
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

    // 衝突判定の境界線を描画するコンポーネント
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();

#endif // _DEBUG

    // 接触時のダメージ
    gameObject->createComponent<Sht2D_DamagePower>(startHitPower, stayHitPowerPerSec);

    // 一定時間後に自身を殺すコンポーネント
    gameObject->createComponent<Sht2D_PlayerExplosionDamageRangeScript>(deleteTime);

    return gameObject;
}
