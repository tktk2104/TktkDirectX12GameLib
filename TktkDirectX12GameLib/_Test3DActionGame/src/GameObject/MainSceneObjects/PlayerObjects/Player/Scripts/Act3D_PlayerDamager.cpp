#include "Act3D_PlayerDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerDamager::start()
{
	m_selfParam = getComponent<Act3D_PlayerParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_PlayerDamager not found Act3D_PlayerParam");
	}
}

void Act3D_PlayerDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// ��A�N�e�B�u��Ԃ������珈�����I����
	if (!isActive()) return;

	// �_���[�W���b�Z�[�W���󂯎������
	if (type.isSame(EventMessageType::Damage))
	{
		// �_���[�W��^����
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// ���񂾂�
		if (m_selfParam->outOfHp())
		{
			// ���S��Ԃ�L���ɂ���
			getGameObject()->stateEnable(PlayerStateType::Dead);

			// ������Ԃ𖳌��ɂ���
			getGameObject()->stateDisable(PlayerStateType::Alive);
		}
		else
		{
			// �_���[�W��Ԃ�L���ɂ���
			getGameObject()->stateEnable(PlayerStateType::Damage);

			// �ʏ��Ԃ𖳌��ɂ���
			getGameObject()->stateDisable(PlayerStateType::Normal);
		}
	}
}
