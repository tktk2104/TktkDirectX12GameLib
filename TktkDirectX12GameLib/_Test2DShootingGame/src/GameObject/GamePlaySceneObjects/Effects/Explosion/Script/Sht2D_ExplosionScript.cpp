#include "Sht2D_ExplosionScript.h"

Sht2D_ExplosionScript::Sht2D_ExplosionScript(float effectEndTimeSec)
	: m_effectEndSecTimer(effectEndTimeSec)
{
}

void Sht2D_ExplosionScript::update()
{
	// �����I���^�C�}�[�J�E���g���O�ȉ���������
	if (m_effectEndSecTimer < 0.0f)
	{
		// ���g�̃I�u�W�F�N�g���폜����
		getGameObject()->destroy();
		return;
	}

	// �����I���^�C�}�[���J�E���g�_�E��
	m_effectEndSecTimer -= tktk::DX12Game::deltaTime();
}