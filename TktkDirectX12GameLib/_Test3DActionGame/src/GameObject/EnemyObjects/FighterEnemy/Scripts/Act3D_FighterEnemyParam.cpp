#include "Act3D_FighterEnemyParam.h"

void Act3D_FighterEnemyParam::damage(int damage)
{
	m_curHp -= damage;

	if (m_curHp <= 0) m_curHp = 0;
}

bool Act3D_FighterEnemyParam::outOfHp() const
{
	return (m_curHp <= 0);
}
