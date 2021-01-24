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

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // プレイヤーの攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(0.2f)
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::PlayerNormalBullet)
        .blendRate(tktkMath::Color_v::blue)
        .create();

    // 長方形の衝突判定コンポーネント
    tktk::RectColliderMaker::makeStart(gameObject)
        .rectSize({ 32.0f, 64.0f })
        .collisionGroupType(CollisionGroup::PlayerBullet)
        .create();

#ifdef _DEBUG

    // 衝突判定の境界線を描画するコンポーネント
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();

#endif // _DEBUG

    // 接触時のダメージ
    gameObject->createComponent<Sht2D_DamagePower>(30.0f, 0.0f);

    // 前方に移動するコンポーネント（毎秒移動速度, 毎秒加速速度）
    gameObject->createComponent<Sht2D_MoveForward>(moveSpeedPerSec, std::numeric_limits<float>::max());

    // 画面外に出たら自身を殺すコンポーネント
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f)
        );

    // プレイヤー通常弾の衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_PlayerNormalBulletCollisionReaction>();

    return gameObject;
}
