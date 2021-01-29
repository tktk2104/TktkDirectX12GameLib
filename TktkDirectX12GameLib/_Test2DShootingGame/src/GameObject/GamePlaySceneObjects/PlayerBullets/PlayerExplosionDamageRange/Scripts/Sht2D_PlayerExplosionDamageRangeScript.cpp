#include "Sht2D_PlayerExplosionDamageRangeScript.h"

Sht2D_PlayerExplosionDamageRangeScript::Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec)
	: m_deadSecTimer(deadTimeSec)
{
}

void Sht2D_PlayerExplosionDamageRangeScript::update()
{
	// 攻撃範囲消滅タイマーカウントが０以下だったら
	if (m_deadSecTimer < 0.0f)
	{
		// 自身のオブジェクトを削除する
		getGameObject()->destroy();
		return;
	}

	// 消滅タイマーをカウントダウン
	m_deadSecTimer -= tktk::DX12Game::deltaTime();
}
