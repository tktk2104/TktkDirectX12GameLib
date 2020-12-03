#include "Act3D_InputToStartDodge.h"

#include "../../../../../Enums/Enums.h"

void Act3D_InputToStartDodge::start()
{
	m_meshDrawer = getComponent<tktk::MeshDrawer>();

	if (m_meshDrawer.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found MeshDrawer");
	}

	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found Transform3D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement3D>();

	if (m_inertialMovement.expired())
	{
		throw std::runtime_error("Act3D_InputToStartDodge not found InertialMovement3D");
	}
}

void Act3D_InputToStartDodge::update()
{
	// ����Ԋu�^�C�}�[���[���ł͂Ȃ����
	if (m_dodgeIntervelSecTimer > 0.0f)
	{
		// �^�C�}�[���J�E���g�_�E��
		m_dodgeIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// ����{�^����������Ă�����
	if (tktk::DX12Game::isTrigger(CommandId::Dodge))
	{
		// �v���C���[�̈ړ����͂��擾����
		auto inputMoveVec = tktk::DX12Game::moveVec();

		// �ړ��������擾����
		auto moveDir	= tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y) * m_transform->getWorldRotation();

		// ��]�������擾����
		auto rotateDir	= tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y);

		// ���b�V���̃��[�J����]���ړ������̕�����������
		m_meshDrawer->setBaseRotation(tktkMath::Quaternion::createFromEulerAngle(
			{ 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up) + 180.0f, 0.0f }
		));

		// ����ړ����n�߂�
		m_inertialMovement->addMomentarilyForce(moveDir.normalized() * DodgeMovePower);

		// �����Ԃɂ���
		getGameObject()->stateEnable(PlayerStateType::Dodge);

		// �ړ���Ԃ�؂�
		getGameObject()->stateDisable(PlayerStateType::Move);

		// ����̃C���^�[�o���^�C�}�[�����Z�b�g����
		m_dodgeIntervelSecTimer = DodgeIntervalTimeSec;
	}
}