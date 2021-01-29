#include "Sht2D_SpreadBulletEnemyBulletCreator.h"

#include "../../../../../Enums/Enums.h"
#include "../../../EnemyBullets/EnemyNormalBullet/Sht2D_EnemyNormalBullet.h"

void Sht2D_SpreadBulletEnemyBulletCreator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_SpreadBulletEnemyBulletCreator not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Sht2D_SpreadBulletEnemyBulletCreator not found InertialMovement2D");
	}
}

void Sht2D_SpreadBulletEnemyBulletCreator::update()
{
	// �e�̔��ˊԊu�^�C�}�[�J�E���g���O�ȏゾ������
	if (m_shotIntervalSecTimer > 0.0f)
	{
		// ���ˊԊu�^�C�}�[���J�E���g�_�E�����Ă��̊֐����I����
		m_shotIntervalSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// �P�x�ɔ��˂���e�̐����������[�v����
	for (size_t i = 0; i < CreateBulletCountPerOnce; i++)
	{
		// ���ˊp�x���v�Z����
		float shotAngle = m_curBaseShotAngleDeg + (360.0f / CreateBulletCountPerOnce * i);

		// �G�̒ʏ�e�𐶐�����
		Sht2D_EnemyNormalBullet::create(
			m_transform->getWorldPosition(),
			shotAngle,
			tktkMath::Matrix3::createRotation(shotAngle).calculateUp() * BulletSpeedPerSec + m_inertialMovement->getVelocity()
		);
	}

	// �e�̔��ˊp�x�̊�l���X�V����
	m_curBaseShotAngleDeg += ShotBulletAngleDistDeg;

	// 360�x���������̕␳�l
	if (m_curBaseShotAngleDeg >= 360.0f) m_curBaseShotAngleDeg -= 360.0f;

	// �e�̔��ˊԊu�^�C�}�[�����Z�b�g����
	m_shotIntervalSecTimer = ShotIntervalTimeSec;
}