#include "Sht2D_PlayerHpBar.h"

#include "../../../../Enums/Enums.h"
#include "Scripts/Sht2D_PlayerHpBarScript.h"

namespace
{
    inline tktk::GameObjectPtr createHpBarContent()
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(tktkMath::Vector2(8.0f, 0.0f))
            .create();

        // 伸縮するHpバーを描画するコンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarContent)
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .blendRate(tktkMath::Color_v::blue)
            .create();

        // Hpバーを伸縮させるコンポーネント
        gameObject->createComponent<Sht2D_PlayerHpBarScript>();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarBackGround()
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .create();

        // Hpバー背景を描画するコンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::HpBarBackGround)
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .create();

        return gameObject;
    }

    inline tktk::GameObjectPtr createHpBarGuide()
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(tktkMath::Vector2(-128.0f, 0.0f))
            .initScaleRate(tktkMath::Vector2(0.4f, 0.4f))
            .create();

        // “プレイヤーHP”の文字を描画するコンポーネント
        tktk::TextDrawer2DMaker::makeStart(gameObject)
            .fontId(FontId::Basic)
            .initText("PlayerHp")
            .centerRate(tktkMath::Vector2(0.0f, 0.5f))
            .create();

        return gameObject;
    }
}

tktk::GameObjectPtr Sht2D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    // ゲームオブジェクトを作る
    tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

    // ゲームプレイシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::GamePlaySceneObject);

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(pos)
        .create();

    // Hpバーの外枠を描画するコンポーネント
    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .spriteMaterialId(SpriteId::HpBarFrame)
        .centerRate(tktkMath::Vector2(0.0f, 0.5f))
        .create();

    // Uiを形成するパーツを自身の子要素に追加する
    gameObject->addChild(createHpBarBackGround());
    gameObject->addChild(createHpBarContent());
    gameObject->addChild(createHpBarGuide());

    return gameObject;
}
