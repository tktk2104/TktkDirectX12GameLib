#include "Sht2D_PlayerMoveScript.h"

#include <stdexcept>

void Sht2D_PlayerMoveScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMoveScript not found Transform2D");
	}

	m_inertialMovement = getComponent<tktk::InertialMovement2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_PlayerMoveScript not found InertialMovement2D");
	}
}

void Sht2D_PlayerMoveScript::update()
{
	// �ړ��������ړ����͕�������擾����i��ʂ̍��W�n�͂��������]���Ă���̂Œ��ӂ��Ă��������j
	tktkMath::Vector2 moveDirection = tktkMath::Vector2::scale(tktk::DX12Game::getMoveInput(), tktkMath::Vector2(1.0f, -1.0f));

	// �p���I�ȗ͂Ƃ��Ċ����ړ��R���|�[�l���g�ŗ͂�������
	m_inertialMovement->addContinuousForce(moveDirection * MoveSpeedPerSec, AccelerationPerSec);

	// ��ʊO�Ƀv���C���[���o�Ă���\�����l�����āA�N�����v����
	tktkMath::Vector2 clampedPos = tktkMath::Vector2::clamp(m_transform->getWorldPosition(), MoveAreaLeftTopPos, MoveAreaRightBottomPos);

	// ��ʓ��␳���s�������W�Ɉړ�������
	m_transform->setWorldPosition(clampedPos);
}