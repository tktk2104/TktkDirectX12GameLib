#include "Sht2D_PlayerHpBar.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerHpBarScript.h"

namespace
{
    inline tktk::GameObjectPtr createHpBarContent()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition({ 8.0f, 0.0f })
            .create();

        // 伸縮するHpバーを描画するコンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarContent)
            .centerRate({ 0.0f, 0.5f })
            .blendRate(tktkMath::Color_v::blue)
            .create();

        // Hpバーを伸縮させるコンポーネント
        gameObject->createComponent<Sht2D_PlayerHpBarScript>();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarBackGround()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // Hpバー背景を描画するコンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarBackGround)
            .centerRate({ 0.0f, 0.5f })
            .create();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarGuide()
    {
        auto gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition({ -128.0f, 0.0f })
            .initScaleRate({ 0.4f })
            .create();

        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .initText("PlayerHp")
            .centerRate({ 0.0f, 0.5f })
            .create();

        return gameObject;
    }
}

tktk::GameObjectPtr Sht2D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(pos)
        .create();

    // Hpバーの外枠を描画するコンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8.0f)
        .spriteMaterialId(SpriteId::HpBarFrame)
        .centerRate({ 0.0f, 0.5f })
        .create();

    // Uiを形成するパーツを自身の子要素に追加する
    gameObject->addChild(createHpBarBackGround());
    gameObject->addChild(createHpBarContent());
    gameObject->addChild(createHpBarGuide());

    return gameObject;
}
