#include "Sht2D_PlayerMissileExplode.h"

#include "../../PlayerExplosionDamageRange/Sht2D_PlayerExplosionDamageRange.h"

Sht2D_PlayerMissileExplode::Sht2D_PlayerMissileExplode(float startHitPower, float stayHitPowerPerSec)
	: m_startHitPower(startHitPower)
	, m_stayHitPowerPerSec(stayHitPowerPerSec)
{
}

void Sht2D_PlayerMissileExplode::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMissileExplode not found Transform2D");
	}
}

void Sht2D_PlayerMissileExplode::explode()
{
	// ƒvƒŒƒCƒ„[‚Ì”š”­UŒ‚”ÍˆÍ‚ð¶¬
	Sht2D_PlayerExplosionDamageRange::create(
		m_transform->getWorldPosition(),
		tktkMath::Vector2(2.0f, 2.0f),
		0.1f,
		0.5f,
		m_startHitPower,
		m_stayHitPowerPerSec
	);

	// Ž©g‚ÌŠŽŽÒ‚ðŽE‚·
	getGameObject()->destroy();
}
