#include "Act3D_BossEnemyStartDown.h"

#include "../../../../../Enums/Enums.h"

void Act3D_BossEnemyStartDown::onEnable()
{
	// �^�C�}�[��������
	m_startDownSecTimer = StartDownTimeSec;
}

void Act3D_BossEnemyStartDown::update()
{
	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_startDownSecTimer < 0.0f)
	{
		// �_�E������Ԃ�L���ɂ���
		getGameObject()->statesEnable({ BossEnemyStateType::Down, BossEnemyStateType::CantMove });

		// �ʏ�A�U���A���s���[�����O��Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ BossEnemyStateType::Normal, BossEnemyStateType::Attack, BossEnemyStateType::MissRool });
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_startDownSecTimer -= tktk::DX12Game::deltaTime();
}
