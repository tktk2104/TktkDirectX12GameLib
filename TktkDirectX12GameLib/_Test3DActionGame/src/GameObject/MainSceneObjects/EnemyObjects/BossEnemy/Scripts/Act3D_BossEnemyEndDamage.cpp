#include "Act3D_BossEnemyEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyEndDamage::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = EndDamageTimeSec;
}

void Act3D_BossEnemyEndDamage::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �_���[�W��Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(BossEnemyStateType::Damage);
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
