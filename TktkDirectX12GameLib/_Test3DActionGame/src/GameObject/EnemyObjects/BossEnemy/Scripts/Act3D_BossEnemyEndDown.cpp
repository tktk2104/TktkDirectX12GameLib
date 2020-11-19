#include "Act3D_BossEnemyEndDown.h"

#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyEndDown::onEnable()
{
	// �^�C�}�[��������
	m_endDownUpSecTimer = EndDownTimeSec;
}

void Act3D_BossEnemyEndDown::update()
{
	if (m_endDownUpSecTimer < 0.0f)
	{
		// �ʏ�A�ړ���Ԃ�L���ɂ���
		getGameObject()->statesEnable({ BossEnemyStateType::Normal, BossEnemyStateType::Move });

		// �_�E������Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ BossEnemyStateType::Down, BossEnemyStateType::StandUp });
		return;
	}

	// �^�C�}�[���X�V����
	m_endDownUpSecTimer -= tktk::DX12Game::deltaTime();
}
