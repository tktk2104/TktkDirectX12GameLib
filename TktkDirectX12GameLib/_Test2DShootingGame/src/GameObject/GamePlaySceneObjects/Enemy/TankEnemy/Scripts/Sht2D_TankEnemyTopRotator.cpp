#include "Sht2D_TankEnemyTopRotator.h"

#include <TktkMath/MathHelper.h>
#include "../../../../../Enums/Enums.h"

void Sht2D_TankEnemyTopRotator::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_TankEnemyTopRotator not found Transform2D");
	}
}

void Sht2D_TankEnemyTopRotator::update()
{
	// �v���C���[�I�u�W�F�N�g���擾
	tktk::GameObjectPtr player = tktk::DX12Game::findGameObjectWithTag(GameObjectTag::Player);

	// �v���C���[�I�u�W�F�N�g���擾�ł��Ȃ���Ί֐����I����
 	if (player.expired()) return;

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾
	tktk::ComponentPtr<tktk::Transform2D> playerTransform = player->getComponent<tktk::Transform2D>();

	// �v���C���[�̍��W�Ǘ��R���|�[�l���g���擾�ł��Ȃ���Ί֐����I����
	if (playerTransform.expired()) return;

	// ���g->�v���C���[�̃x�N�g�����v�Z
	tktkMath::Vector2 selfToPlayer = playerTransform->getWorldPosition() + TargetOffset - m_transform->getWorldPosition();

	// ��]����p�x�̍ő�l
	float rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToPlayer) - m_transform->getWorldRotationDeg();

	// �t���␳
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// ��]����p�x
	float rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * RotateSpeedPerSecDeg;

	// �t���[�����̈ړ��ʂɕ␳
	rotateDist *= tktk::DX12Game::deltaTime();

	// ��]�p�x����
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// ��]�p�x���X�V����
	m_transform->addLocalRotationDeg(rotateDist);
}