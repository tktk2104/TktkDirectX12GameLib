#include "Act3D_EnemyAttackRange.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_EnemyAttackRange::create(const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // エネミー攻撃範囲タグを追加
    gameObject->addGameObjectTag(GameObjectTag::EnemyAttackRange);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(scale)
        .create();

    // OBB衝突判定コンポーネント
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 1.0f, 1.0f, 1.0f })
        .localPosition({ 0.0f, 0.0f, 0.0f })
        .collisionGroupType(CollisionGroup::EnemyDamageRange)
        .extrudedRate(0.0f)
        .create();

    // 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::red)
        .create();
#endif // _DEBUG

    return gameObject;
}
