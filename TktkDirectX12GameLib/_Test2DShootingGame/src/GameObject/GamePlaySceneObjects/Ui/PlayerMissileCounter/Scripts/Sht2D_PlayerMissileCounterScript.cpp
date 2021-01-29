#include "Sht2D_PlayerMissileCounterScript.h"

#include "../../../../../Enums/Enums.h"

namespace
{
    tktk::GameObjectPtr createMissileIcon(const tktkMath::Vector2& position)
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(position)
            .create();

        // スプライト描画コンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::MissileCounterIcon)
            .create();

        return gameObject;
    }
}

void Sht2D_PlayerMissileCounterScript::start()
{
    // プレイヤーオブジェクトを取得する
    tktk::GameObjectPtr playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

    if (playerObject.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found PlayerObject");
    }

    // プレイヤーオブジェクトから残弾数コンポーネントを取得する
    m_playerBulletCount = playerObject->getComponent<Sht2D_PlayerBulletCount>();

    if (m_playerBulletCount.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found Sht2D_PlayerBulletCount");
    }

    // プレイヤーミサイルの残弾アイコンオブジェクト配列のメモリをミサイル最大数分だけ確保する
    m_missileIconObjectArray.reserve(m_playerBulletCount->getMaxMissileCount());

    // プレイヤーミサイル最大数分だけループする
    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        // ミサイルの残弾アイコンオブジェクトを作る
        tktk::GameObjectPtr createdIcon = createMissileIcon(tktkMath::Vector2(MissileIconXInterval * i, 0.0f));

        // 作ったミサイルの残弾アイコンが非表示にされるべきアイコンだったらアクティブフラグを折る
        if (i >= m_playerBulletCount->getCurMissileCount()) createdIcon->setActive(false);

        // 自身のオブジェクトの子要素に作ったオブジェクトを追加する
        getGameObject()->addChild(createdIcon);

        // プレイヤーミサイルの残弾アイコンオブジェクト配列に作ったオブジェクトを追加する
        m_missileIconObjectArray.push_back(createdIcon);
    }
}

void Sht2D_PlayerMissileCounterScript::update()
{
    // プレイヤーの残弾数コンポーネントが存在しなかったら関数を終える
    if (m_playerBulletCount.expired()) return;

    // プレイヤーミサイル最大数分だけループする
    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        // それぞれの残弾アイコンのアクティブフラグを現在のミサイル残弾数を使って変更する
        m_missileIconObjectArray.at(i)->setActive(i < m_playerBulletCount->getCurMissileCount());
    }
}
