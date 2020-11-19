#include "Act3D_PlayerAttackRangeGenerator.h"

#include "../../PlayerAttackRange/Act3D_PlayerAttackRange.h"

Act3D_PlayerAttackRangeGenerator::Act3D_PlayerAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
	: m_generateTimeSec(generateTimeSec)
	, m_deleteTimeSec(deleteTimeSec)
{
	m_attackRange = Act3D_PlayerAttackRange::create(position, scale);
}

void Act3D_PlayerAttackRangeGenerator::start()
{
	getGameObject()->addChild(m_attackRange);
}

void Act3D_PlayerAttackRangeGenerator::onEnable()
{
	m_attackRangeSecTimer = 0.0f;
}

void Act3D_PlayerAttackRangeGenerator::onDisable()
{
	m_attackRange->setActive(false);
}

void Act3D_PlayerAttackRangeGenerator::update()
{
	if (m_attackRangeSecTimer < m_deleteTimeSec)
	{
		m_attackRangeSecTimer += tktk::DX12Game::deltaTime();

		if (m_attackRangeSecTimer > m_generateTimeSec)m_attackRange->setActive(true);
		return;
	}
	m_attackRange->setActive(false);
}
