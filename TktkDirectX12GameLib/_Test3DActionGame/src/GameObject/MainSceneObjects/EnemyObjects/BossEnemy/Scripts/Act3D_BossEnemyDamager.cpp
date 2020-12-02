#include "Act3D_BossEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

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
	// ��A�N�e�B�u��Ԃ������珈�����I����
	if (!isActive()) return;

	// ��_���[�W�ʒm���󂯎������
	if (type.isSame(EventMessageType::Damage))
	{
		// �_���[�W��^����
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// ���񂾂�
		if (m_selfParam->outOfHp())
		{
			// ���S��Ԃ�L���ɂ���
			getGameObject()->stateEnable(BossEnemyStateType::Dead);

			// ������Ԃ𖳌��ɂ���
			getGameObject()->stateDisable(BossEnemyStateType::Alive);
		}
		else
		{
			// �_���[�W��Ԃ�L���ɂ���
			getGameObject()->stateEnable(BossEnemyStateType::Damage);
		}
	}
}