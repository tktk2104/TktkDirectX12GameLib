#include "Sht2D_Flame.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_FlameScript.h"

tktk::GameObjectPtr Sht2D_Flame::create(const tktkMath::Vector2& position, float rotate)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // 二次元座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(position)
        .initRotationDeg(rotate)
        .create();

    // スプライト描画コンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::Flame)
        .centerRate(tktkMath::Vector2(0.5f, 1.0f))
        .create();

    // 炎エフェクトのアニメーションコンポーネント
    gameObject->createComponent<Sht2D_FlameScript>();

    return gameObject;
}