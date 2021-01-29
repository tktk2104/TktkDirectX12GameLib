#include "Sht2D_LockOnIcon.h"

#include "../../../../Enums/Enums.h"

tktk::GameObjectPtr Sht2D_LockOnIcon::create()
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    // ロックオンアイコンを描画するコンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::LockOnTarget)
        .create();

    return gameObject;
}
