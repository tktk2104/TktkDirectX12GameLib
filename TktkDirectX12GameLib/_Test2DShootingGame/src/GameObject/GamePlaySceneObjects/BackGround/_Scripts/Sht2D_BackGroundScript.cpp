#include "Sht2D_BackGroundScript.h"

Sht2D_BackGroundScript::Sht2D_BackGroundScript(const tktkMath::Vector2& velocityPerSec)
	: m_velocityPerSec(velocityPerSec)
{
}

void Sht2D_BackGroundScript::start()
{
	m_transform = getComponent<tktk::Transform2D>();

	if (m_transform.expired())
	{
		throw std::runtime_error("Sht2D_BackGroundScript not found Transform2D");
	}
}

void Sht2D_BackGroundScript::update()
{
	// ˆÚ“®‘¬“x•ªŽ©g‚ðˆÚ“®‚³‚¹‚é
	m_transform->addLocalPosition(m_velocityPerSec * tktk::DX12Game::deltaTime());
}
