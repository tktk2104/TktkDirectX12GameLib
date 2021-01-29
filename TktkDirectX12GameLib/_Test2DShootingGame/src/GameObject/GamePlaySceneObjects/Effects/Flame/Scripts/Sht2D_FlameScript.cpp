#include "Sht2D_FlameScript.h"

void Sht2D_FlameScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_FlameScript not found Transform2D");
	}
}

void Sht2D_FlameScript::update()
{
	// �X�P�[�����O�^�C�}�[���J�E���g�A�b�v����
	m_scalingSecTimer += tktk::DX12Game::deltaTime();

	// �X�P�[�����O�^�C�}�[���ő�l�ɒB���Ă�����l�����Z�b�g����
	if (m_scalingSecTimer > ScalingMaxTimeSec) m_scalingSecTimer = 0.0f;

	// �X�P�[�����O�^�C�}�[�̒l���g���ăX�P�[�����v�Z����
	const tktkMath::Vector2& calculateScale = tktkMath::Vector2(
		m_transform->getLocalScaleRate().x,
		1.0f + (std::abs(m_scalingSecTimer - ScalingMaxTimeSec / 2.0f) / (ScalingMaxTimeSec / 2.0f) * (MaxYScaleRate - 1.0f))
	);

	// �v�Z�����l�ōX�V����
	m_transform->setLocalScaleRate(calculateScale);
}
