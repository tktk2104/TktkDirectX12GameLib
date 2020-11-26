#include "Act3D_PlayerHpBar.h"

#include "../../../Enums/Enums.h"

#include "Scripts/Act3D_PlayerHpBarContentScript.h"

inline tktk::GameObjectPtr createPlayerHpBarContent()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition({ 8.0f, 0.0f })
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(7.0f)
        .spriteMaterialId(SpriteId::PlayerHpBar)
        .centerRate({ 0.0f, 0.5f })
        .create();

    gameObject->createComponent<Act3D_PlayerHpBarContentScript>();

    return gameObject;
}

inline tktk::GameObjectPtr createPlayerHpBarBackGround()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(6.0f)
        .spriteMaterialId(SpriteId::HpBarBackGround)
        .centerRate({ 0.0f, 0.5f })
        .create();

    return gameObject;
}

inline tktk::GameObjectPtr createPlayerHpBarGuide()
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition({ 16.0f, -32.0f })
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(9.0f)
        .spriteMaterialId(SpriteId::PlayerHpBarGuide)
        .create();

    return gameObject;
}

tktk::GameObjectPtr Act3D_PlayerHpBar::create(const tktkMath::Vector2& pos)
{
    auto gameObject = tktk::DX12Game::createGameObject();

    // メインシーンが終わると消えるオブジェクトを表すタグ
    gameObject->addGameObjectTag(GameObjectTag::MainSceneObject);

    // 座標管理コンポーネント
    tktk::Transform2DMaker::makeStart(gameObject)
        .initPosition(pos)
        .create();

    tktk::SpriteDrawerMaker::makeStart(gameObject)
        .drawPriority(8.0f)
        .spriteMaterialId(SpriteId::HpBarFrame)
        .centerRate({ 0.0f, 0.5f })
        .create();

    gameObject->addChild(createPlayerHpBarBackGround());
    gameObject->addChild(createPlayerHpBarContent());
    gameObject->addChild(createPlayerHpBarGuide());

    return gameObject;
}
