#include "Sht2D_PlayerMissileCounterScript.h"

#include "../../../../../Enums/Enums.h"

namespace
{
    tktk::GameObjectPtr createMissileIcon(const tktkMath::Vector2& position)
    {
        auto gameObject = tktk::DX12Game::createGameObject();

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
    auto playerObject = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

    if (playerObject.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found PlayerObject");
    }

    m_playerBulletCount = playerObject->getComponent<Sht2D_PlayerBulletCount>();

    if (m_playerBulletCount.expired())
    {
        throw std::runtime_error("Sht2D_PlayerMissileCounterScript not found Sht2D_PlayerBulletCount");
    }

    m_missileIconObjectArray.reserve(m_playerBulletCount->getMaxMissileCount());

    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        auto createdIcon = createMissileIcon({ MissileIconXInterval * i, 0.0f });

        if (i >= m_playerBulletCount->getCurMissileCount()) createdIcon->setActive(false);

        getGameObject()->addChild(createdIcon);

        m_missileIconObjectArray.push_back(createdIcon);
    }
}

void Sht2D_PlayerMissileCounterScript::update()
{
    if (m_playerBulletCount.expired()) return;

    for (int i = 0; i < m_playerBulletCount->getMaxMissileCount(); i++)
    {
        m_missileIconObjectArray.at(i)->setActive(i < m_playerBulletCount->getCurMissileCount());
    }
}
