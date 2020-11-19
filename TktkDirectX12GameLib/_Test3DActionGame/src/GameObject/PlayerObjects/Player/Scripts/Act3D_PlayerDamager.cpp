#include "Act3D_PlayerDamager.h"

#include "../../../../Enums/Enums.h"

void Act3D_PlayerDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::Damage))
	{
		// ダメージ状態をアクティブに
		getGameObject()->stateEnable(PlayerStateType::Damage);

		// 通常ステートを非アクティブに
		getGameObject()->stateDisable(PlayerStateType::Normal);
	}
}
