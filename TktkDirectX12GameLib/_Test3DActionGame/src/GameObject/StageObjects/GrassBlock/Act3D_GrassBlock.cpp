#include "Act3D_GrassBlock.h"

#include "../../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_GrassBlock::create(const tktkMath::Vector3& position)
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initPosition(position)
        .initScaleRate(2.0f)
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(BasicMeshId::GrassBlock)
        .baseScale(1.0f)
        .create();

    // OBB衝突判定コンポーネント
    tktk::BoxColliderMaker::makeStart(gameObject)
        .boxSize({ 1.0f, 1.0f, 1.0f })
        .collisionGroupType(CollisionGroup::Stage)
        .isExtrude(true)
        .extrudedRate(0.0f)
        .create();

    // 衝突判定範囲描画コンポーネント
#ifdef _DEBUG
    tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
        .lineColor(tktkMath::Color_v::white)
        .create();
#endif // _DEBUG

    return gameObject;
}
