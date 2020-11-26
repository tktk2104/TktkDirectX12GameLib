#include "Act3D_PlayerParam.h"

void Act3D_PlayerParam::damage(int damage)
{
    m_curHp -= damage;

    if (m_curHp <= 0) m_curHp = 0;
}

bool Act3D_PlayerParam::outOfHp() const
{
    return (m_curHp <= 0);
}

int Act3D_PlayerParam::getCurHp() const
{
    return m_curHp;
}
