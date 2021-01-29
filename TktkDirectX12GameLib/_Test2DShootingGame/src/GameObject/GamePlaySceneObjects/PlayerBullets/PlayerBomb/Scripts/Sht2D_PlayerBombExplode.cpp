#include "Sht2D_PlayerBombExplode.h"

#include "../../PlayerExplosionDamageRange/Sht2D_PlayerExplosionDamageRange.h"

Sht2D_PlayerBombExplode::Sht2D_PlayerBombExplode(float startHitPower, float stayHitPowerPerSec)
	: m_startHitPower(startHitPower)
	, m_stayHitPowerPerSec(stayHitPowerPerSec)
{
}

void Sht2D_PlayerBombExplode::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerBombExplode not found Transform2D");
	}
}

void Sht2D_PlayerBombExplode::explode()
{
	// ƒvƒŒƒCƒ„[‚Ì”š”­UŒ‚”ÍˆÍ‚ð¶¬
	Sht2D_PlayerExplosionDamageRange::create(
		m_transform->getWorldPosition(),
		tktkMath::Vector2(8.0f, 8.0f),
		0.05f,
		1.0f,
		m_startHitPower,
		m_stayHitPowerPerSec
	);

	// Ž©g‚ÌŠŽŽÒ‚ðŽE‚·
	getGameObject()->destroy();
}
