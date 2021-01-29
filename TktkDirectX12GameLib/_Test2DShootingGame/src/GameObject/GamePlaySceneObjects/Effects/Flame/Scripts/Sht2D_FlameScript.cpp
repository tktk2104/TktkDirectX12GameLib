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
	// スケーリングタイマーをカウントアップする
	m_scalingSecTimer += tktk::DX12Game::deltaTime();

	// スケーリングタイマーが最大値に達していたら値をリセットする
	if (m_scalingSecTimer > ScalingMaxTimeSec) m_scalingSecTimer = 0.0f;

	// スケーリングタイマーの値を使ってスケールを計算する
	const tktkMath::Vector2& calculateScale = tktkMath::Vector2(
		m_transform->getLocalScaleRate().x,
		1.0f + (std::abs(m_scalingSecTimer - ScalingMaxTimeSec / 2.0f) / (ScalingMaxTimeSec / 2.0f) * (MaxYScaleRate - 1.0f))
	);

	// 計算した値で更新する
	m_transform->setLocalScaleRate(calculateScale);
}
