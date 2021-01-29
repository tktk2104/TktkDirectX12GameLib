#include "Sht2D_PlayerBombCounterScript.h"

#include "../../../../../Enums/Enums.h"

namespace
{
    tktk::GameObjectPtr createBombIcon(const tktkMath::Vector2& position)
    {
        // ゲームオブジェクトを作る
        tktk::GameObjectPtr gameObject = tktk::DX12Game::createGameObject();

        // 二次元座標管理コンポーネント
        tktk::Transform2DMaker::makeStart(gameObject)
            .initPosition(position)
            .create();

        // スプライト描画コンポーネント
        tktk::SpriteDrawerMaker::makeStart(gameObject)
            .spriteMaterialId(SpriteId::BompCounterIcon)
            .create();

        return gameObject;
    }
}

void Sht2D_PlayerBombCounterScript::start()
{
    // プレイヤーオブジェクトを取得する
    tktk::GameObjectPtr playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

    if (playerObject.expired())
    {
        throw std::runtime_error("Sht2D_PlayerBombCounterScript not found PlayerObject");
    }

    // プレイヤーオブジェクトから残弾数コンポーネントを取得する
    m_playerBulletCount = playerObject->getComponent<Sht2D_PlayerBulletCount>();

    if (m_playerBulletCount.expired())
    {
        throw std::runtime_error("Sht2D_PlayerBombCounterScript not found Sht2D_PlayerBulletCount");
    }

    // プレイヤーボムの残弾アイコンオブジェクト配列のメモリをボム最大数分だけ確保する
    m_bombIconObjectArray.reserve(m_playerBulletCount->getMaxBombCount());

    // プレイヤーボム最大数分だけループする
    for (int i = 0; i < m_playerBulletCount->getMaxBombCount(); i++)
    {
        // ボムの残弾アイコンオブジェクトを作る
        tktk::GameObjectPtr createdIcon = createBombIcon(tktkMath::Vector2(BombIconXInterval * i, 0.0f));

        // 作ったボムの残弾アイコンが非表示にされるべきアイコンだったらアクティブフラグを折る
        if (i >= m_playerBulletCount->getCurBombCount()) createdIcon->setActive(false);

        // 自身のオブジェクトの子要素に作ったオブジェクトを追加する
        getGameObject()->addChild(createdIcon);

        // プレイヤーボムの残弾アイコンオブジェクト配列に作ったオブジェクトを追加する
        m_bombIconObjectArray.push_back(createdIcon);
    }
}

void Sht2D_PlayerBombCounterScript::update()
{
    // プレイヤーの残弾数コンポーネントが存在しなかったら関数を終える
    if (m_playerBulletCount.expired()) return;

    // プレイヤーボム最大数分だけループする
    for (int i = 0; i < m_playerBulletCount->getMaxBombCount(); i++)
    {
        // それぞれの残弾アイコンのアクティブフラグを現在のボム残弾数を使って変更する
        m_bombIconObjectArray.at(i)->setActive(i < m_playerBulletCount->getCurBombCount());
    }
}
