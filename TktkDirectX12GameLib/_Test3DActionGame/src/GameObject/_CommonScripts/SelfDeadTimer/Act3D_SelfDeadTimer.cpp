#include "Act3D_SelfDeadTimer.h"

Act3D_SelfDeadTimer::Act3D_SelfDeadTimer(float deadTimeSec)
	: m_deadTimeSec(deadTimeSec)
{
}

void Act3D_SelfDeadTimer::start()
{
	// タイマーを初期化
	m_deadSecTimer = m_deadTimeSec;
}

void Act3D_SelfDeadTimer::update()
{
	// タイマーのカウントがゼロになったら
	if (m_deadSecTimer < 0.0f)
	{
		// このコンポーネントの所持者を殺す
		getGameObject()->destroy();
		return;
	}

	// タイマーをカウントダウン
	m_deadSecTimer -= tktk::DX12Game::deltaTime();
}
