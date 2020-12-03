#include "Act3D_BossEnemyParam.h"

void Act3D_BossEnemyParam::update()
{
    // 各種タイマーのカウントダウン処理
    if (m_normalAttackIntervalSecTimer > 0.0f)
    {
        m_normalAttackIntervalSecTimer -= tktk::DX12Game::deltaTime();
    }

    if (m_rollAttackIntervalSecTimer > 0.0f)
    {
        m_rollAttackIntervalSecTimer -= tktk::DX12Game::deltaTime();
    }

    if (m_jumpAttackIntervalSecTimer > 0.0f)
    {
        m_jumpAttackIntervalSecTimer -= tktk::DX12Game::deltaTime();
    }
}

void Act3D_BossEnemyParam::damage(int damage)
{
    m_curHp -= damage;

    // Hpの値がマイナスにならないための処理
    if (m_curHp <= 0) m_curHp = 0;
}

bool Act3D_BossEnemyParam::outOfHp() const
{
    return (m_curHp <= 0);
}

bool Act3D_BossEnemyParam::canNormalAttack() const
{
    return (m_normalAttackIntervalSecTimer <= 0.0f);
}

void Act3D_BossEnemyParam::resetNormalAttackIntervelTimer(float time)
{
    m_normalAttackIntervalSecTimer = time;
}

bool Act3D_BossEnemyParam::canRollAttack() const
{
    return (m_rollAttackIntervalSecTimer <= 0.0f);
}

void Act3D_BossEnemyParam::resetRollAttackIntervelTimer(float time)
{
    m_rollAttackIntervalSecTimer = time;
}

bool Act3D_BossEnemyParam::canJumpAttack() const
{
    return (m_jumpAttackIntervalSecTimer <= 0.0f);
}

void Act3D_BossEnemyParam::resetJumpAttackIntervelTimer(float time)
{
    m_jumpAttackIntervalSecTimer = time;
}
