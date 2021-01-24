#include "Sht2D_PlayerBulletCount.h"

void Sht2D_PlayerBulletCount::changeMissileCount(int changeWidth)
{
    m_curMissileCount += changeWidth;

    // �~�T�C�������}�C�i�X�̒l�ɂȂ�Ȃ����߂̏���
    if (m_curMissileCount < 0) m_curMissileCount = 0;

    // �~�T�C����������𒴂��Ȃ����߂̏���
    if (m_curMissileCount > getMaxMissileCount()) m_curMissileCount = getMaxMissileCount();
}

int Sht2D_PlayerBulletCount::getCurMissileCount() const
{
    return m_curMissileCount;
}

void Sht2D_PlayerBulletCount::changeBombCount(int changeWidth)
{
    m_curBombCount += changeWidth;

    // �{�������}�C�i�X�̒l�ɂȂ�Ȃ����߂̏���
    if (m_curBombCount < 0) m_curBombCount = 0;

    // �{����������𒴂��Ȃ����߂̏���
    if (m_curBombCount > getMaxBombCount()) m_curBombCount = getMaxBombCount();
}

int Sht2D_PlayerBulletCount::getCurBombCount() const
{
    return m_curBombCount;
}