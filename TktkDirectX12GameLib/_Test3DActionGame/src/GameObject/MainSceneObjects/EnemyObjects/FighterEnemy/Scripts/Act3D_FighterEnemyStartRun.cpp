#include "Act3D_FighterEnemyStartRun.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartRun::onEnable()
{
	// �^�C�}�[��������
	m_startRunSecTimer = StartRunTimeSec;
}

void Act3D_FighterEnemyStartRun::update()
{
	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_startRunSecTimer < 0.0f)
	{
		// �����Ԃ�L���ɂ���
		getGameObject()->stateEnable(FighterEnemyState::Run);

		// ������Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(FighterEnemyState::Walk);
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_startRunSecTimer -= tktk::DX12Game::deltaTime();
}
