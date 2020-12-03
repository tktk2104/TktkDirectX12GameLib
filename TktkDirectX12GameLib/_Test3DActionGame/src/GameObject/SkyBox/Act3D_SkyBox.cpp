#include "Act3D_SkyBox.h"

#include "../../Enums/Enums.h"

tktk::GameObjectPtr Act3D_SkyBox::create()
{
    // ゲームオブジェクトを作成
    auto gameObject = tktk::DX12Game::createGameObject();

    // ３次元座標コンポーネント
    tktk::Transform3DMaker::makeStart(gameObject)
        .initScaleRate(1.0f)
        .traceType(tktk::TraceParentType::tracePos) // 親の回転とスケーリングを無視する
        .create();

    // メッシュ描画コンポーネント
    tktk::MeshDrawerMaker::makeStart(gameObject)
        .meshId(MeshId::SkyBox)
        .baseScale(100.0f)
        .create();

    return gameObject;
}
