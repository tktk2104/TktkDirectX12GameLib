#include "Act3D_PlayerDamager.h"

#include "../../../../Enums/Enums.h"

void Act3D_PlayerDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::Damage))
	{
		// �_���[�W��Ԃ��A�N�e�B�u��
		getGameObject()->stateEnable(PlayerStateType::Damage);

		// �ʏ�X�e�[�g���A�N�e�B�u��
		getGameObject()->stateDisable(PlayerStateType::Normal);
	}
}
