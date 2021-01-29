#include "Sht2D_ExplosionScript.h"

Sht2D_ExplosionScript::Sht2D_ExplosionScript(float effectEndTimeSec)
	: m_effectEndSecTimer(effectEndTimeSec)
{
}

void Sht2D_ExplosionScript::update()
{
	// 爆発終了タイマーカウントが０以下だったら
	if (m_effectEndSecTimer < 0.0f)
	{
		// 自身のオブジェクトを削除する
		getGameObject()->destroy();
		return;
	}

	// 爆発終了タイマーをカウントダウン
	m_effectEndSecTimer -= tktk::DX12Game::deltaTime();
}