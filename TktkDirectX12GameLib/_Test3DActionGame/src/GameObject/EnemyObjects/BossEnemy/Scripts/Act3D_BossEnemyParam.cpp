#include "Act3D_BossEnemyParam.h"

void Act3D_BossEnemyParam::damage(int damage)
{
    m_curHp -= damage;

    if (m_curHp <= 0) m_curHp = 0;
}

bool Act3D_BossEnemyParam::outOfHp() const
{
    return (m_curHp <= 0);
}