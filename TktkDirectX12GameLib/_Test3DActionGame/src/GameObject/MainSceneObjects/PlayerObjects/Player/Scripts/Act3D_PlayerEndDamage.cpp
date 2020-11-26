#include "Act3D_PlayerEndDamage.h"

#include "../../../../../Enums/Enums.h"

void Act3D_PlayerEndDamage::onEnable()
{
	// �^�C�}�[��������
	m_endDamageSecTimer = EndDamageTimeSec;
}

void Act3D_PlayerEndDamage::update()
{
	if (m_endDamageSecTimer < 0.0f)
	{
		// �ʏ��Ԃ�L���ɂ���
		getGameObject()->stateEnable(PlayerStateType::Normal);

		// �_���[�W��Ԃ𖳌��ɂ���
		getGameObject()->stateDisable(PlayerStateType::Damage);
		return;
	}

	// �^�C�}�[���X�V����
	m_endDamageSecTimer -= tktk::DX12Game::deltaTime();
}
