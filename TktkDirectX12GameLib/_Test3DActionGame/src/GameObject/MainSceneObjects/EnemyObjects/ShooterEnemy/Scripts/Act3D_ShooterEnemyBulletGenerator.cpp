#include "Act3D_ShooterEnemyBulletGenerator.h"

#include <stdexcept>
#include "../../../../../Enums/Enums.h"
#include "../../EnemyBullet/ShooterEnemyBullet/Act3D_ShooterEnemyBullet.h"

void Act3D_ShooterEnemyBulletGenerator::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FindPlayer not found Transform3D");
	}
}

void Act3D_ShooterEnemyBulletGenerator::onEnable()
{
	// ���˃t���O��܂�
	m_endShot = false;

	// �^�C�}�[������������
	m_generateSecTimer = GenerateTimeSec;
}

void Act3D_ShooterEnemyBulletGenerator::update()
{
	// ���ɒe�𔭎˂��Ă����珈�����I����
	if (m_endShot) return;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾�ł��Ă��Ȃ����
	if (m_playerTransform.expired())
	{
		// �v���C���[�I�u�W�F�N�g���擾����
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ώ������I����
		if (player.expired()) return;

		// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾����
		m_playerTransform = player->getComponent<tktk::Transform3D>();

		// �v���C���[�����W�Ǘ��R���|�[�l���g�������Ă��Ȃ���Ώ������I����
		if (m_playerTransform.expired()) return;
	}

	// �^�C�}�[�̃J�E���g���[���ɂȂ��Ă�����
	if (m_generateSecTimer < 0.0f)
	{
		const auto& selfPos		= m_selfTransform->getWorldPosition();
		const auto& playerPos	= m_playerTransform->getWorldPosition();

		// ���˂���e�̔��˕���
		auto bulletDirection = (playerPos - selfPos).normalized();

		// �������U���G�l�~�[�̒e�𐶐�����
		Act3D_ShooterEnemyBullet::create(selfPos + GeneratePos, bulletDirection * BulletSpeed);

		// �e�̔��˃t���O�𗧂Ă�
		m_endShot = true;
	}

	// �^�C�}�[���J�E���g�_�E������
	m_generateSecTimer -= tktk::DX12Game::deltaTime();
}
