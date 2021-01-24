#include "Sht2D_PlayerBombCounterScript.h"

#include "../../../../../Enums/Enums.h"

namespace
{
    tktk::GameObjectPtr createBombIcon(const tktkMath::Vector2& position)
    {
        auto gameObject = tktk::DX12Game::createGameObject();

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
    auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

    if (playerObject.expired())
    {
        throw std::runtime_error("Sht2D_PlayerBombCounterScript not found PlayerObject");
    }

    m_playerBulletCount = playerObject->getComponent<Sht2D_PlayerBulletCount>();

    if (m_playerBulletCount.expired())
    {
        throw std::runtime_error("Sht2D_PlayerBombCounterScript not found Sht2D_PlayerBulletCount");
    }

    m_bombIconObjectArray.reserve(m_playerBulletCount->getMaxBombCount());

    for (int i = 0; i < m_playerBulletCount->getMaxBombCount(); i++)
    {
        auto createdIcon = createBombIcon({ BombIconXInterval * i, 0.0f });

        if (i >= m_playerBulletCount->getCurBombCount()) createdIcon->setActive(false);

        getGameObject()->addChild(createdIcon);

        m_bombIconObjectArray.push_back(createdIcon);
    }
}

void Sht2D_PlayerBombCounterScript::update()
{
    if (m_playerBulletCount.expired()) return;

    for (int i = 0; i < m_playerBulletCount->getMaxBombCount(); i++)
    {
        m_bombIconObjectArray.at(i)->setActive(i < m_playerBulletCount->getCurBombCount());
    }
}
