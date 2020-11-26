#include "Act3D_ShooterEnemyEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_ShooterEnemyEndDamage::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = EndDamageTimeSec;
}

void Act3D_ShooterEnemyEndDamage::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ʏ��Ԃ�L���ɂ���
		getGameObject()->stateEnable(ShooterEnemyStateType::Normal);

		// �_���[�W��Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(ShooterEnemyStateType::Damage);
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
