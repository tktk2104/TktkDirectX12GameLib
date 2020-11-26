#include "Act3D_FighterEnemyDamager.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyDamager::start()
{
	m_selfParam = getComponent<Act3D_FighterEnemyParam>();

	if (m_selfParam.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyDamager not found Act3D_FighterEnemyParam");
	}
}

void Act3D_FighterEnemyDamager::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	if (type.isSame(EventMessageType::Damage))
	{
		// �_���[�W��^����
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
				getGameObject()->statesEnable({FighterEnemyState::Move, FighterEnemyState::Walk});

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
