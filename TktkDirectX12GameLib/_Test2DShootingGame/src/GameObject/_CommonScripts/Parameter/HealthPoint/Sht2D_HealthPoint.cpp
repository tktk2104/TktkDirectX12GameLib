#include "Sht2D_HealthPoint.h"

Sht2D_HealthPoint::Sht2D_HealthPoint(float maxHp)
    : m_maxHp(maxHp)
    , m_curHp(maxHp)
{
}

void Sht2D_HealthPoint::damage(float damage)
{
    m_curHp -= damage;

    // HP���}�C�i�X�̒l�ɂȂ�Ȃ����߂̏���
    if (m_curHp < 0.0f) m_curHp = 0.0f;
}

bool Sht2D_HealthPoint::outOfHp() const
{
    return (m_curHp <= 0.0f);
}

float Sht2D_HealthPoint::getCurHp() const
{
    return m_curHp;
}

float Sht2D_HealthPoint::getMaxHp() const
{
    return m_maxHp;
}
