#include "Sht2D_PlayerBombCreator.h"

#include "../../../../Enums/Enums.h"
#include "../../PlayerBullets/PlayerBomb/Sht2D_PlayerBomb.h"
#include "../../PlayerBullets/PlayerBomb/Scripts/Sht2D_PlayerBombExplode.h"

void Sht2D_PlayerBombCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombCreator not found Transform2D");
	}

	m_playerBulletCount = getComponent<Sht2D_PlayerBulletCount>();

	if (m_playerBulletCount.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombCreator not found Sht2D_PlayerBulletCount");
	}
}

void Sht2D_PlayerBombCreator::update()
{
	if (m_shotIntervalSecTimer > 0.0f)
	{
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	if (tktk::DX12Game::isPush(CommandId::ShotBomb))
	{
		if (m_targetBombObject.expired())
		{
			createBomb();
		}
		else
		{
			explodeBomb();
		}
	}
}

void Sht2D_PlayerBombCreator::createBomb()
{
	if (m_playerBulletCount->getCurBombCount() <= 0) return;

	m_targetBombObject = Sht2D_PlayerBomb::create(tktkMath::Vector2(0.0f, -64.0f) * m_transform->calculateWorldMatrix(), m_transform->getWorldRotationDeg(), BombSpeedPerSec, BombActiveTimeSec);

	m_playerBulletCount->changeBombCount(-1);
}

void Sht2D_PlayerBombCreator::explodeBomb()
{
	// 爆弾がアクティブ状態で無ければ起爆できない
	if (!m_targetBombObject->containState(PlayerBombStateType::Active)) return;

	// 起爆！
	m_targetBombObject->getComponent<Sht2D_PlayerBombExplode>()->explode();

	m_targetBombObject = tktk::GameObjectPtr();

	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}
