#include "Act3D_RotateToPlayerInTime.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../Enums/Enums.h"

Act3D_RotateToPlayerInTime::Act3D_RotateToPlayerInTime(float roteteSpeedPerSecDeg, float rotateEndTimeSec)
	: m_roteteSpeedPerSecDeg(roteteSpeedPerSecDeg)
	, m_rotateEndTimeSec(rotateEndTimeSec)
{
}

void Act3D_RotateToPlayerInTime::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FindPlayer not found Transform3D");
	}
}

void Act3D_RotateToPlayerInTime::onEnable()
{
	// �^�C�}�[������������
	m_rotateEndSecTimer = m_rotateEndTimeSec;
}

void Act3D_RotateToPlayerInTime::update()
{
	// �^�C�}�[�̃J�E���g���[���������珈�����I����
	if (m_rotateEndSecTimer < 0.0f) return;

	// �^�C�}�[���J�E���g�_�E������
	m_rotateEndSecTimer -= tktk::DX12Game::deltaTime();

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾�ł��Ă��Ȃ���΁A
	if (m_playerTransform.expired())
	{
		// �v���C���[�I�u�W�F�N�g���擾����
		auto player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

		// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ώ������I����
		if (player.expired()) return;

		// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾����
		m_playerTransform = player->getComponent<tktk::Transform3D>();

		// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾�ł��Ȃ���Ώ������I����
		if (m_playerTransform.expired()) return;
	}

	// ���g����v���C���[�ւ̕������v�Z����
	auto selfToPlayer = (m_playerTransform->getWorldPosition() - m_selfTransform->getWorldPosition()).normalized();

	// �v���C���[�����ւ̂�����̉�]�̍����擾����i�x���@�j
	auto targetAngle = tktkMath::Vector2::signedAngle({ selfToPlayer.x, selfToPlayer.z }, tktkMath::Vector2_v::up);

	// ��]����ׂ��p�x���擾����
	auto rotateDist = targetAngle - m_selfTransform->calculateLocalEulerAngles().y;

	// ��]�p�x��180�x���z���Ă�����t��]�ɂ���
	if (std::abs(rotateDist) > 180.0f) rotateDist -= 360.0f * tktkMath::MathHelper::sign(rotateDist);

	// ��]���x�����߂�
	auto roteteSpeed = m_roteteSpeedPerSecDeg * tktk::DX12Game::deltaTime();

	// ��]�p�x�����߂�
	auto rotateWidth = (std::abs(rotateDist) > roteteSpeed) ? (roteteSpeed * tktkMath::MathHelper::sign(rotateDist)) : rotateDist;

	// ���g����]������
	m_selfTransform->addLocalEulerAngles(tktkMath::Vector3(0.0f, rotateWidth, 0.0f));
}
