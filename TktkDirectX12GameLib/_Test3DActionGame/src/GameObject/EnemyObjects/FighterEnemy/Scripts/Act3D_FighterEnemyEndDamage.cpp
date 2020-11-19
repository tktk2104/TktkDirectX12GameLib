#include "Act3D_FighterEnemyEndDamage.h"

#include "../../../../Enums/Enums.h"

void Act3D_FighterEnemyEndDamage::onEnable()
{
	// �^�C�}�[��������
	m_endAttackSecTimer = EndDamageTimeSec;
}

void Act3D_FighterEnemyEndDamage::update()
{
	if (m_endAttackSecTimer < 0.0f)
	{
		// �ʏ��Ԃ�L���ɂ���
		getGameObject()->stateEnable(FighterEnemyState::Normal);

		// �_���[�W��Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(FighterEnemyState::Damage);
		return;
	}

	// �^�C�}�[���X�V����
	m_endAttackSecTimer -= tktk::DX12Game::deltaTime();
}
