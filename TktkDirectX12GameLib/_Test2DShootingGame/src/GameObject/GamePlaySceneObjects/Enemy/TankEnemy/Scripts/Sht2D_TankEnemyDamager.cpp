#include "Sht2D_TankEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Sht2D_TankEnemyDamager::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyDamager not found Transform2D");
	}

	m_healthPoint = getComponent<Sht2D_HealthPoint>();

	if (m_healthPoint.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyDamager not found Sht2D_HealthPoint");
	}
}

void Sht2D_TankEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// ��A�N�e�B�u��Ԃ������珈�����I����
	if (!isActive()) return;

	// �_���[�W���b�Z�[�W���󂯎������
	if (type.isSame(EventMessageType::Damage))
	{
		// �_���[�W��^����
		m_healthPoint->damage(*attachment.getValuePtr<float>().lock());

		// ���g�̗̑͂��O�ȉ���������
		if (m_healthPoint->outOfHp())
		{
			// ���g�̏�Ԃ𐶑���Ԃ��玀�S��ԂɑJ�ڂ�����
			getGameObject()->stateDisable(TankEnemyStateTypes::Alive);
			getGameObject()->stateEnable(TankEnemyStateTypes::Dead);
		}
	}
}
