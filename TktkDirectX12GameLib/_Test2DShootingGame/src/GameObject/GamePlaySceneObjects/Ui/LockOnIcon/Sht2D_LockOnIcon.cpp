#include "Sht2D_LockOnIcon.h"

#include "../../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_LockOnIcon::create()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    // ロックオンアイコンを描画するコンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8.0f)
        .spriteMaterialId(SpriteId::LockOnTarget)
        .create();

    return gameObject;
}
