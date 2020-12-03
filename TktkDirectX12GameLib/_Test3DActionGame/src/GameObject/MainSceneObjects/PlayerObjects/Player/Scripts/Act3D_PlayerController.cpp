#include "Act3D_PlayerController.h"

#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

Act3D_PlayerController::Act3D_PlayerController(float moveSpeedPerSec, float rotateDegSpeedPerSec)
	: m_moveSpeedPerSec(moveSpeedPerSec)
	, m_rotateDegSpeedPerSec(rotateDegSpeedPerSec)
{
}

void Act3D_PlayerController::start()
{
	m_transform = getComponent<tktk::Transform3D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Act3D_PlayerController not found Transform3D");
	}
}

void Act3D_PlayerController::update()
{
	// �ړ��������s��
	move();

	// ��]�������s��
	rotate();
}

void Act3D_PlayerController::handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment)
{
	if (!isActive()) return;

	// �G�̕����������郁�b�Z�[�W���͂�����
	if (type.isSame(EventMessageType::LookToEnemy))
	{
		// �ł��߂��G�̕��������������s��
		lookMostNearEnemy();
	}
}

void Act3D_PlayerController::move()
{
	// �ړ��Ɋ֌W����X�e�[�g����U�S�Đ؂�
	getGameObject()->stateDisable(PlayerStateType::Idle);
	getGameObject()->stateDisable(PlayerStateType::WalkForward);
	getGameObject()->stateDisable(PlayerStateType::WalkBackward);
	getGameObject()->stateDisable(PlayerStateType::WalkLeft);
	getGameObject()->stateDisable(PlayerStateType::WalkRight);
	getGameObject()->stateDisable(PlayerStateType::RunForward);

	// ���̈ړ��Ɋւ���X�e�[�g
	auto playerMoveState = PlayerStateType::Idle;

	// �ړ����x
	auto moveSpeed = m_moveSpeedPerSec;

	// �v���C���[�̈ړ����͂��擾����
	auto inputMoveVec = tktk::DX12Game::moveVec();

	// �ł������ړ����͂̒l
	auto mostStrongMoveInputPower = 0.0f;

	// ���͕����ɂ���ăv���C���[�̈ړ��X�e�[�g��ς���
	if (inputMoveVec.y > mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkForward;
		mostStrongMoveInputPower = inputMoveVec.y;
	}
	if (inputMoveVec.y < -mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkBackward;
		mostStrongMoveInputPower = -inputMoveVec.y;
	}
	if (inputMoveVec.x < -mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkLeft;
		mostStrongMoveInputPower = -inputMoveVec.x;
	}
	if (inputMoveVec.x > mostStrongMoveInputPower)
	{
		playerMoveState = PlayerStateType::WalkRight;
		mostStrongMoveInputPower = inputMoveVec.x;
	}

	// �����O���ړ���Ԃ̏ꍇ�A
	if (playerMoveState == PlayerStateType::WalkForward)
	{
		// ����{�^�������͂���Ă�����
		if (tktk::DX12Game::isPush(CommandId::Run))
		{
			// �v���C���[��O�������Ԃɂ���
			playerMoveState = PlayerStateType::RunForward;

			// �ړ����x�𑁂�����
			moveSpeed *= 2.0f;
		}
	}

	// ���͂���ړ��������v�Z����
	auto moveDir = tktkMath::Vector3(inputMoveVec.x, 0.0f, inputMoveVec.y) * m_transform->getWorldRotation();

	// ���g�̍��W�Ǘ��R���|�[�l���g�ɍ��W�ړ��ʂ�n��
	m_transform->addWorldPosition(moveDir * moveSpeed * tktk::DX12Game::deltaTime());

	// �V���Ȉړ��X�e�[�g��ݒ肷��
	getGameObject()->stateEnable(playerMoveState);
}

void Act3D_PlayerController::rotate()
{
	// �G������{�^����������Ă�����
	if (tktk::DX12Game::isPush(CommandId::LookEnemy))
	{
		// �ł��߂��G�̕��������������s��
		lookMostNearEnemy();
	}

	// �v���C���[�̎��_�ړ����͂��擾����
	auto inputMoveVec = tktk::DX12Game::lookVec();

	// ���g�̍��W�Ǘ��R���|�[�l���g�ɉ�]�ω��ʂ�n��
	m_transform->addLocalEulerAngles({ 0.0f,  inputMoveVec.x * m_rotateDegSpeedPerSec * tktk::DX12Game::deltaTime(), 0.0f });
}

void Act3D_PlayerController::lookMostNearEnemy()
{
	// �G�l�~�[�I�u�W�F�N�g�̃��X�g���擾����
	auto enemyObjects = tktk::DX12Game::findGameObjectsWithTag(GameObjectTag::Enemy);

	// �G�����݂��Ȃ���Ώ������I����
	if (enemyObjects.empty()) return;

	// �ł��߂��G�ւ̋���
	auto minDist = std::numeric_limits<float>::max();

	// �ł��߂��G�̍��W�Ǘ��R���|�[�l���g
	tktk::ComponentPtr<tktk::Transform3D> nearEnemyTransform;

	// �S�ẴG�l�~�[�I�u�W�F�N�g�����񂷂�
	for (const auto& enemyObject : enemyObjects)
	{
		// ���W�Ǘ��R���|�[�l���g�̈ꎞ�ۑ��ϐ�
		auto tempEnemyTransform = enemyObject->getComponent<tktk::Transform3D>();

		// �v���C���[�ƃG�l�~�[�̋��������߂�
		auto dist = tktkMath::Vector3::distance(m_transform->getWorldPosition(), tempEnemyTransform->getWorldPosition());

		// �����̋߂����X�V���Ă�����
		if (dist < minDist)
		{
			// �����Ƃ��߂��G�̍��W�Ǘ��R���|�[�l���g���X�V����
			nearEnemyTransform = tempEnemyTransform;

			// �ł��߂��������X�V����
			minDist = dist;
		}
	}

	// ���g�������ׂ������̃x�N�g�������߂�
	auto rotateDir = nearEnemyTransform->getWorldPosition() - m_transform->getWorldPosition();

	// ���g�̍��W�Ǘ��R���|�[�l���g�Ɍ����ׂ���]������n��
	m_transform->setLocalEulerAngles({ 0.0f, tktkMath::Vector2::signedAngle({ rotateDir.x, rotateDir.z }, tktkMath::Vector2_v::up), 0.0f });
}
