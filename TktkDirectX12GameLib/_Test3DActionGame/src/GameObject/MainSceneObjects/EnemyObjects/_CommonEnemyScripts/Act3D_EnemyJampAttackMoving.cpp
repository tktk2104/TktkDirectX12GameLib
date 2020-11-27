#include "Act3D_EnemyJampAttackMoving.h"

Act3D_EnemyJampAttackMoving::Act3D_EnemyJampAttackMoving(float jumpVerticalPower, float jmupVerticalMoveStartTimeSec, float jumpHorizontalSpeedPerSec, float jmupHorizontalMoveTimeSec)
	: m_jumpVerticalPower(jumpVerticalPower)
	, m_jmupVerticalMoveStartTimeSec(jmupVerticalMoveStartTimeSec)
	, m_jumpHorizontalSpeedPerSec(jumpHorizontalSpeedPerSec)
	, m_jmupHorizontalMoveTimeSec(jmupHorizontalMoveTimeSec)
{
}

void Act3D_EnemyJampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found Transform3D");
	}
	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_EnemyJampAttackMoving not found InertialMovement3D");
	}

}

void Act3D_EnemyJampAttackMoving::onEnable()
{
	// �����o�ϐ�������������
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_EnemyJampAttackMoving::update()
{
	// �����ړ��J�n�^�C�}�[���w��̒l�ɒB���Ă��Ȃ����
	if (m_verticalMoveSecTimer < m_jmupVerticalMoveStartTimeSec)
	{
		// �^�C�}�[���J�E���g�A�b�v
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	// �����ړ����J�n��������������Ă����
	else if (!m_afterVerticalMove)
	{
		// ���������ɔ�ђ��˂�
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * m_jumpVerticalPower);

		// �����ړ���t���O�𗧂Ă�
		m_afterVerticalMove = true;
	}

	// �����ړ��^�C�}�[���w��̒l�ɒB���Ă��Ȃ����
	if (m_horizontalMoveSecTimer < m_jmupHorizontalMoveTimeSec)
	{
		// �^�C�}�[���J�E���g�A�b�v
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		// ���g�̍��W�Ǘ��R���|�[�l���g�Ɉړ�����n��
		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * m_jumpHorizontalSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}
