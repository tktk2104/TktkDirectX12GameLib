#include "Sht2D_RoteteToObject.h"

#include <TktkMath/MathHelper.h>

Sht2D_RoteteToObject::Sht2D_RoteteToObject(float rotateSpeedPerSecDeg, const tktk::GameObjectPtr& rotateTarget)
	: m_rotateSpeedPerSecDeg(rotateSpeedPerSecDeg)
{
	// ��]�ΏۃI�u�W�F�N�g�����݂��Ȃ�������֐����I����
	if (rotateTarget.expired()) return;

	// ��]�ΏۃI�u�W�F�N�g������W�Ǘ��R���|�[�l���g���擾����
	m_roteteTargetTransform			= rotateTarget->getComponent<tktk::Transform2D>();
}

void Sht2D_RoteteToObject::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_RoteteToObject not found Transform2D");
	}
}

void Sht2D_RoteteToObject::update()
{
	// ��]�Ώۂ̍��W�Ǘ��R���|�[�l���g�����݂��Ȃ�������֐����I����
	if (m_roteteTargetTransform.expired()) return;

	// ���g->�^�[�Q�b�g�̃x�N�g�����v�Z
	auto selfToTarget = m_roteteTargetTransform->getWorldPosition() - m_transform->getWorldPosition();

	// ��]����p�x�̍ő�l
	auto rotateMaxDist = tktkMath::Vector2::signedAngle(tktkMath::Vector2_v::down, selfToTarget) - m_transform->getWorldRotationDeg();

	// �t���␳
	if (std::abs(rotateMaxDist) > 180.0f) rotateMaxDist -= tktkMath::MathHelper::sign(rotateMaxDist) * 360.0f;

	// ��]����p�x
	auto rotateDist = tktkMath::MathHelper::sign(rotateMaxDist) * m_rotateSpeedPerSecDeg;

	// �t���[�����̈ړ��ʂɕ␳
	rotateDist *= tktk::DX12Game::deltaTime();

	// ��]�p�x����
	if (std::abs(rotateDist) > std::abs(rotateMaxDist)) rotateDist = tktkMath::MathHelper::sign(rotateDist) * std::abs(rotateMaxDist);

	// ��]�p�x���X�V����
	m_transform->addLocalRotationDeg(rotateDist);
}
