#include "Act3D_BossEnemyDamager.h"

#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_BossEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_BossEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::Damage))
	{
		// ƒ_ƒ[ƒW‚ð—^‚¦‚é
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// Ž€‚ñ‚¾‚ç
		if (m_selfParam->outOfHp())
		{
			// Ž€–Só‘Ô‚ð—LŒø‚É‚·‚é
			getGameObject()->stateEnable(FighterEnemyState::Dead);

			// ¶‘¶ó‘Ô‚ð–³Œø‚É‚·‚é
			getGameObject()->stateDisable(FighterEnemyState::Alive);
		}
	}
}