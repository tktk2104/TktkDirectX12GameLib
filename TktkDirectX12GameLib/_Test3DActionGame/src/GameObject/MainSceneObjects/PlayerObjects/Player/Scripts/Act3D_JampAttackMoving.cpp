#include "Act3D_JampAttackMoving.h"

void Act3D_JampAttackMoving::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found Transform3D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_JampAttackMoving not found InertialMovement3D");
	}
}

void Act3D_JampAttackMoving::onEnable()
{
	// �����o�ϐ�������������
	m_verticalMoveSecTimer		= 0.0f;
	m_afterVerticalMove			= false;
	m_horizontalMoveSecTimer	= 0.0f;
}

void Act3D_JampAttackMoving::update()
{
	// �����ړ��J�n�^�C�}�[���w��̒l�ɒB���Ă��Ȃ����
	if (m_verticalMoveSecTimer < JmupVerticalMoveStartTimeSec)
	{
		// �^�C�}�[���J�E���g�A�b�v
		m_verticalMoveSecTimer += tktk::DX12Game::deltaTime();
	}
	// �����ړ����J�n��������������Ă����
	else if (!m_afterVerticalMove)
	{
		// ���������ɔ�ђ��˂�
		m_inertialMovement->addMomentarilyForce(m_transform->calculateWorldUp().normalized() * JumpVerticalPower);

		// �����ړ���t���O�𗧂Ă�
		m_afterVerticalMove = true;
	}

	// �����ړ��^�C�}�[���w��̒l�ɒB���Ă��Ȃ����
	if (m_horizontalMoveSecTimer < JmupHorizontalMoveTimeSec)
	{
		// �^�C�}�[���J�E���g�A�b�v
		m_horizontalMoveSecTimer += tktk::DX12Game::deltaTime();

		// �����ړ����x
		auto jumpSpeedPerSec = JumpHorizontalSpeedPerSec;

		// �O�����ւ̓��͂����ȉ��������瑬�x����������
		if (tktk::DX12Game::moveVec().y < 0.5f) jumpSpeedPerSec *= 0.5f;

		// ���g�̍��W�Ǘ��R���|�[�l���g�Ɉړ�����n��
		m_transform->addLocalPosition(m_transform->calculateWorldForwardLH().normalized() * jumpSpeedPerSec * tktk::DX12Game::deltaTime());
		return;
	}
}