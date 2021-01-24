#include "Sht2D_DamagePower.h"

Sht2D_DamagePower::Sht2D_DamagePower(float startHitPower, float stayHitPowerPerSec)
    : m_startHitPower(startHitPower)
    , m_stayHitPowerPerSec(stayHitPowerPerSec)
{
}

float Sht2D_DamagePower::getStartHitPower() const
{
    return m_startHitPower;
}

float Sht2D_DamagePower::getStayHitPowerPerSec() const
{
    return m_stayHitPowerPerSec;
}
