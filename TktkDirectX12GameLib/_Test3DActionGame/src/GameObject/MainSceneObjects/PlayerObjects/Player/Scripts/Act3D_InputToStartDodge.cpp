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
	if (m_dodgeIntervelSecTimer > 0.0f)
	{
		m_dodgeIntervelSecTimer -= tktk::DX12Game::deltaTime();
		return;
	}

	// ����{�^����������Ă�����
	if (tktk::DX12Game::isTrigger(CommandId::Dodge))
	{
		// �ړ��������擾����
		auto moveDir = tktkMath::Vector3_v::zero;

		// ��]�������擾����
		auto rotateDir = tktkMath::Vector3_v::zero;

		if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_A))
		{
			moveDir -= m_transform->calculateWorldRight();
			rotateDir -= tktkMath::Vector3_v::right;
		}
		if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_D))
		{
			moveDir += m_transform->calculateWorldRight();
			rotateDir += tktkMath::Vector3_v::right;
		}
		if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_W))
		{
			moveDir += m_transform->calculateWorldForwardLH();
			rotateDir += tktkMath::Vector3_v::forwardLH;
		}
		if (tktk::DX12Game::isPush(tktk::KeybordKeyType::key_S))
		{
			moveDir -= m_transform->calculateWorldForwardLH();
			rotateDir -= tktkMath::Vector3_v::forwardLH;
		}

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