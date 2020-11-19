#include "Act3D_EnemyAttackRangeGenerator.h"

#include "../EnemyAttackRange/Act3D_EnemyAttackRange.h"

Act3D_EnemyAttackRangeGenerator::Act3D_EnemyAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
	: m_generateTimeSec(generateTimeSec)
	, m_deleteTimeSec(deleteTimeSec)
{
	m_attackRange = Act3D_EnemyAttackRange::create(position, scale);
}

void Act3D_EnemyAttackRangeGenerator::start()
{
	getGameObject()->addChild(m_attackRange);
}

void Act3D_EnemyAttackRangeGenerator::onEnable()
{
	m_attackRangeSecTimer = 0.0f;
}

void Act3D_EnemyAttackRangeGenerator::onDisable()
{
	m_attackRange->setActive(false);
}

void Act3D_EnemyAttackRangeGenerator::update()
{
	if (m_attackRangeSecTimer < m_deleteTimeSec)
	{
		m_attackRangeSecTimer += tktk::DX12Game::deltaTime();

		if (m_attackRangeSecTimer > m_generateTimeSec)m_attackRange->setActive(true);
		return;
	}
	m_attackRange->setActive(false);
}
