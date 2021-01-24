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
	if (m_scalingSecTimer > ScalingMaxTimeSec) m_scalingSecTimer = 0.0f;

	m_scalingSecTimer += tktk::DX12Game::deltaTime();

	const auto& curScale = m_transform->getLocalScaleRate();

	m_transform->setLocalScaleRate({ curScale.x, 1.0f + (std::abs(m_scalingSecTimer - ScalingMaxTimeSec / 2.0f) / (ScalingMaxTimeSec / 2.0f) * (MaxYScaleRate - 1.0f)) });
}
