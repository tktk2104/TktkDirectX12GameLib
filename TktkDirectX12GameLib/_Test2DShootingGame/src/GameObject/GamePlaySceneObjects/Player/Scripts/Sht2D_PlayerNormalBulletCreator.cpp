#include "Sht2D_PlayerNormalBulletCreator.h"

#include "../../../../Enums/Enums.h"
#include "../../PlayerBullets/PlayerNormalBullet/Sht2D_PlayerNormalBullet.h"

void Sht2D_PlayerNormalBulletCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerNormalBulletCreator not found Transform2D");
	}
}

void Sht2D_PlayerNormalBulletCreator::update()
{
	// �e�̔��ˊԊu�^�C�}�[�J�E���^���O�ȏゾ������
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// �J�E���g�_�E�����Ċ֐����I����
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// �e���˓��͂�������Ă�����
	if (tktk::DX12Game::isPush(CommandId::ShotBullet))
	{
		// �v���C���[�ʏ�e�����i�������W�A��������]�A�e���ˑ��x�j
		Sht2D_PlayerNormalBullet::create(tktkMath::Vector2(0.0f, -64.0f) * m_transform->calculateWorldMatrix(), m_transform->getWorldRotationDeg(), BulletSpeedPerSec);

		// �e�̔��ˊԊu�^�C�}�[������������
		m_shotIntervalSecTimer = ShotIntervalTimeSec;
	}
}
