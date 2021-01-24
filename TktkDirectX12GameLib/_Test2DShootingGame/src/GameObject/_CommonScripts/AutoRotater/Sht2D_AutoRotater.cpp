#include "Sht2D_AutoRotater.h"

Sht2D_AutoRotater::Sht2D_AutoRotater(float rotateSpeedPerSec)
	: m_rotateSpeedPerSec(rotateSpeedPerSec)
{
}

void Sht2D_AutoRotater::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_AutoRotater not found Transform2D");
	}
}

void Sht2D_AutoRotater::update()
{
	m_transform->addLocalRotationDeg(m_rotateSpeedPerSec * tktk::DX12Game::deltaTime());
}
