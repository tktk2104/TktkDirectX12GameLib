#include "Act3D_PlayerAttackRange.h"

#include "../../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_PlayerAttackRange::create(const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // プレイヤー攻撃範囲タグを追加
    gameObject->addGameObjectTag(GameObjectTag::PlayerAttackRange);

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(scale)
        .create();

    // OBB衝突判定コンポーネント
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 1.0f, 1.0f, 1.0f })
        .localPosition({ 0.0f, 0.0f, 0.0f })
        .collisionGroupType(CollisionGroup::PlayerDamageRange)
        .extrudedRate(0.0f)
        .create();

// 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::blue)
        .create();
#endif // _DEBUG

    return gameObject;
}
