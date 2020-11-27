#include "Act3D_FighterEnemyStartAttack.h"

#include <stdexcept>
#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

void Act3D_FighterEnemyStartAttack::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_FighterEnemyStartAttack not found Transform3D");
	}
}

void Act3D_FighterEnemyStartAttack::update()
{
	// �U���Ԋu�^�C�}�[�̃J�E���g���[���łȂ����
	if (m_attackIntervelSecTimer > 0.0f)
	{
		// �^�C�}�[�̃J�E���g�_�E�����s���A�������I����
		m_attackIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

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

	// ���g�ƃv���C���[�̍��W�̍����v�Z����
	auto posDist = tktkMath::Vector3::distance(m_selfTransform->getWorldPosition(), m_playerTransform->getWorldPosition());

	// �ʏ�U�����s�������𖞂����Ă����
	if (posDist < NormalAttackStartRange && std::abs(rotateDist) < NormalAttackStartAngleDeg)
	{
		// �ʏ�U����Ԃ�L���ɂ���
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::Punch });
		
		// �ړ���Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		// �U���Ԋu�^�C�}�[��ʏ�U���̒l�ŏ���������
		m_attackIntervelSecTimer = NormalAttackIntervalTimeSec;
	}

	// �W�����v�U�����s�������𖞂����Ă����
	else if (posDist < JumpAttackStartRange && std::abs(rotateDist) < JumpAttackStartAngleDeg)
	{
		// �W�����v�U����Ԃ�L���ɂ���
		getGameObject()->statesEnable({ FighterEnemyState::Attack, FighterEnemyState::JumpAttack });
		
		// �ړ���Ԃ𖳌��ɂ���
		getGameObject()->statesDisable({ FighterEnemyState::Move, FighterEnemyState::Walk, FighterEnemyState::Run });

		// �U���Ԋu�^�C�}�[���W�����v�U���̒l�ŏ���������
		m_attackIntervelSecTimer = JumpAttackIntervalTimeSec;
	}
}
