#include "Act3D_ShooterEnemyParam.h"

void Act3D_ShooterEnemyParam::damage(int damage)
{
    m_curHp -= damage;

    // HPがマイナスの値にならないように修正
    if (m_curHp <= 0) m_curHp = 0;
}

bool Act3D_ShooterEnemyParam::outOfHp() const
{
    return (m_curHp <= 0);
}
