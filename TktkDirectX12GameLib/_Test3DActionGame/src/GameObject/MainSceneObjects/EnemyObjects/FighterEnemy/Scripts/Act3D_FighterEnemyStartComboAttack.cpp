#include "Act3D_FighterEnemyStartComboAttack.h"

#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartComboAttack::onEnable()
{
	// �^�C�}�[��������
	m_startComboSecTimer = StartComboTimeSec;
}

void Act3D_FighterEnemyStartComboAttack::update()
{
	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_startComboSecTimer < 0.0f)
	{
		// �X���C�v�U����Ԃ�L���ɂ���
		getGameObject()->stateEnable(FighterEnemyState::Swiping);

		// �p���`�U����Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(FighterEnemyState::Punch);
		return;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_startComboSecTimer -= tktk::DX12Game::deltaTime();
}
