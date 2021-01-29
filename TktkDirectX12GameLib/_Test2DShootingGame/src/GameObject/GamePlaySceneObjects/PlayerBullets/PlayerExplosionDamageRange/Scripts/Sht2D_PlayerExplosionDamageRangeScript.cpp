#include "Sht2D_PlayerExplosionDamageRangeScript.h"

Sht2D_PlayerExplosionDamageRangeScript::Sht2D_PlayerExplosionDamageRangeScript(float deadTimeSec)
	: m_deadSecTimer(deadTimeSec)
{
}

void Sht2D_PlayerExplosionDamageRangeScript::update()
{
	// �U���͈͏��Ń^�C�}�[�J�E���g���O�ȉ���������
	if (m_deadSecTimer < 0.0f)
	{
		// ���g�̃I�u�W�F�N�g���폜����
		getGameObject()->destroy();
		return;
	}

	// ���Ń^�C�}�[���J�E���g�_�E��
	m_deadSecTimer -= tktk::DX12Game::deltaTime();
}
