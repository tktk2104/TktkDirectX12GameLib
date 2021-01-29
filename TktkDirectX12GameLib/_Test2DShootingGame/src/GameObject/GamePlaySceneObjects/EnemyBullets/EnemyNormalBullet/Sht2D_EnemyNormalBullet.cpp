#include "Sht2D_EnemyNormalBullet.h"

#include "../../../../Enums/Enums.h"
#include "Scripts//Sht2D_EnemyNormalBulletCollisionReaction.h"
#include "../../../_CommonScripts/Parameter/DamagePower/Sht2D_DamagePower.h"
#include "../../../_CommonScripts/OutGameAreaObjectDeleter/Sht2D_OutGameAreaObjectDeleter.h"

tktk::GameObjectPtr Sht2D_EnemyNormalBullet::create(const tktkMath::Vector2& position, float rotate, const tktkMath::Vector2& velocity)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 敵の攻撃範囲であることを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .initScaleRate(tktkMath::Vector2(0.2f, 0.2f))
        .create();

    // 二次元慣性移動コンポーネント
    tktk::InertialMovement2DMaker::makeStart(gameObject)
        .decelerationPerSec(0.0f)
        .initVelocity(velocity)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::PlayerNormalBullet)
        .blendRate(tktkMath::Color_v::red)
        .create();

    // 長方形の衝突判定コンポーネント
    tktk::RectColliderMaker::makeStart(gameObject)
        .rectSize(tktkMath::Vector2(32.0f, 64.0f))
        .collisionGroupType(CollisionGroup::EnemyBullet)
        .create();

#ifdef _DEBUG

    // 衝突判定の境界線を描画するコンポーネント
    tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();

#endif // _DEBUG

    // 接触時のダメージ（接触開始時ダメージ、毎秒の接触中ダメージ）
    gameObject->createComponent<Sht2D_DamagePower>(10.0f, 0.0f);

    // 画面外に出たら自身を殺すコンポーネント（画面範囲の左上座標、画面範囲の右下座標）
    gameObject->createComponent<Sht2D_OutGameAreaObjectDeleter>(
        tktkMath::Vector2(-256.0f, -256.0f),
        tktk::DX12Game::getScreenSize() + tktkMath::Vector2(256.0f, 256.0f)
        );

    // エネミー通常弾の衝突判定リアクションコンポーネント
    gameObject->createComponent<Sht2D_EnemyNormalBulletCollisionReaction>();

    return gameObject;
}
