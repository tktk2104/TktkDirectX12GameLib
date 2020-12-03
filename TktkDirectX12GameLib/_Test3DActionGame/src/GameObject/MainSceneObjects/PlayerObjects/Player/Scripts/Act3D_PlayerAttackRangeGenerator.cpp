#include "Act3D_PlayerAttackRangeGenerator.h"

#include "../../PlayerAttackRange/Act3D_PlayerAttackRange.h"

Act3D_PlayerAttackRangeGenerator::Act3D_PlayerAttackRangeGenerator(float generateTimeSec, float deleteTimeSec, const tktkMath::Vector3& position, const tktkMath::Vector3& scale)
	: m_generateTimeSec(generateTimeSec)
	, m_deleteTimeSec(deleteTimeSec)
{
	// �v���C���[�̍U���͈͂𐶐�����
	m_attackRange = Act3D_PlayerAttackRange::create(position, scale);
}

void Act3D_PlayerAttackRangeGenerator::start()
{
	// �v���C���[�̍U���͈͂����g����������I�u�W�F�N�g�̎q�v�f�ɐݒ肷��
	getGameObject()->addChild(m_attackRange);
}

void Act3D_PlayerAttackRangeGenerator::onEnable()
{
	// �^�C�}�[������������
	m_attackRangeSecTimer = 0.0f;
}

void Act3D_PlayerAttackRangeGenerator::onDisable()
{
	// �U���͈͂��A�N�e�B�u�ɂ���
	m_attackRange->setActive(false);
}

void Act3D_PlayerAttackRangeGenerator::update()
{
	// �U���͈͂��폜���鎞�ԂɒB���Ă��Ȃ����
	if (m_attackRangeSecTimer < m_deleteTimeSec)
	{
		// �^�C�}�[�̃J�E���g�A�b�v
		m_attackRangeSecTimer += tktk::DX12Game::deltaTime();

		// �U���͈͂𐶐����鎞�ԂɒB���Ă�����A�N�e�B�u��Ԃɂ���
		if (m_attackRangeSecTimer > m_generateTimeSec) m_attackRange->setActive(true);
		return;
	}
	// �U���͈͂��폜���鎞�ԂɒB���Ă������A�N�e�B�u��Ԃɂ���
	m_attackRange->setActive(false);
}
