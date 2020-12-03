#include "Act3D_ShooterEnemyBullet.h"

#include "../../../../../Enums/Enums.h"

#include "../../../../_CommonScripts/SelfDeadTimer/Act3D_SelfDeadTimer.h"
#include "../../_CommonEnemyScripts/Act3D_MoveForward.h"

tktk::GameObjectPtr Act3D_ShooterEnemyBullet::create(const tktkMath::Vector3& position, const tktkMath::Vector3& velocityPerSec)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // メインシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // エネミー弾タグを追加
    gameObject->addGameObjectTag(GameObjectTag::EnemyBullet);

    // エネミー攻撃範囲タグを追加
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotation(tktkMath::Quaternion::createLookRotation(velocityPerSec))
        .initScaleRate(1.0f)
        .create();

    // 単色メッシュを描画するコンポーネント
    tktk::MonoColorMeshDrawerMaker::makeStart(gameObject)
        .setSphereMeshWireFrame()
        .baseScale(0.2f)
        .albedoColor(tktkMath::Color_v::red)
        .create();

    // 球体衝突判定コンポーネント
    tktk::SphereColliderMaker::makeStart(gameObject)
        .radius(0.1f)
        .collisionGroupType(CollisionGroup::EnemyDamageRange)
        .extrudedRate(0.0f)
        .create();

    // 拡散するビルボードパーティクルコンポーネント
    tktk::BillboardSpreadEffectCreatorMaker::makeStart(gameObject)
        .billboardMaterialId(BillBoardId::Spark)
        .billboardBlendRate(tktkMath::Color_v::red)
        .moveSpeedPerSec(0.5f)
        .generateLocalPosRandomRange({ 0.5f, 0.5f, 0.5f })
        .create();

    // 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    /*tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();*/
#endif // _DEBUG

    // 10秒間で自身を殺すコンポーネント
    gameObject->createComponent<Act3D_SelfDeadTimer>(10.0f);

    // 前方に移動するコンポーネント
    gameObject->createComponent<Act3D_MoveForward>(velocityPerSec.length());

    return gameObject;
}