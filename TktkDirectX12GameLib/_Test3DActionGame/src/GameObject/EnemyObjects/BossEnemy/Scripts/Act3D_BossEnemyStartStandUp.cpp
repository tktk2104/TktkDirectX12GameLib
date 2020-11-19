#include "Act3D_BossEnemyStartStandUp.h"

#include "../../../../Enums/Enums.h"

void Act3D_BossEnemyStartStandUp::onEnable()
{
	// �^�C�}�[��������
	m_startStandUpSecTimer = StartStandUpTimeSec;
}

void Act3D_BossEnemyStartStandUp::update()
{
	if (m_startStandUpSecTimer < 0.0f)
	{
		// �N���オ���Ԃ�L���ɂ���
		getGameObject()->stateEnable(BossEnemyStateType::StandUp);

		// �_�E������Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(BossEnemyStateType::CantMove);
		return;
	}

	// �^�C�}�[���X�V����
	m_startStandUpSecTimer -= tktk::DX12Game::deltaTime();
}
