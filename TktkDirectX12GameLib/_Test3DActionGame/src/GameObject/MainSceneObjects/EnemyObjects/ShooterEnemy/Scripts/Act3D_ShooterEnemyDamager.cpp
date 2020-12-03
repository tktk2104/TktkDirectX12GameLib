#include "Act3D_ShooterEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_ShooterEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_ShooterEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_ShooterEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	// ��A�N�e�B�u��Ԃ������牽�����Ȃ�
	if (!isActive()) return;

	// �󂯎�������b�Z�[�W����_���[�W���b�Z�[�W��������
	if (type.isSame(EventMessageType::Damage))
	{
		// ���g�Ƀ_���[�W��^����
		m_selfParam->damage(*attachment.getValuePtr<int>().lock());

		// ���񂾂�
		if (m_selfParam->outOfHp())
		{
			// ���S��Ԃ�L���ɂ���
			getGameObject()->stateEnable(FighterEnemyState::Dead);

			// ������Ԃ𖳌��ɂ���
			getGameObject()->stateDisable(FighterEnemyState::Alive);
		}
		else
		{
			// �����ҋ@��Ԃ�������
			if (getGameObject()->containState(FighterEnemyState::Idle))
			{
				// ������Ԃ�L���ɂ���
				getGameObject()->statesEnable({ FighterEnemyState::Move, FighterEnemyState::Walk });

				// �ҋ@��Ԃ𖳌��ɂ���
				getGameObject()->stateDisable(FighterEnemyState::Idle);
			}

			// �_���[�W��Ԃ�L���ɂ���
			getGameObject()->stateEnable(FighterEnemyState::Damage);

			// �ʏ��Ԃ𖳌��ɂ���
			getGameObject()->stateDisable(FighterEnemyState::Normal);
		}
	}
}
