#include "Act3D_TitleCameraScript.h"

void Act3D_TitleCameraScript::start()
{
	m_selfTransform = getComponent<tktk::Transform3D>();

	if (m_selfTransform.expired())
	{
		throw std::runtime_error("Act3D_TitleCameraScript not found Transform3D");
	}
}

void Act3D_TitleCameraScript::update()
{
	m_selfTransform->addWorldEulerAngles({ 0.0f, RotateSpeedPerSecDeg * tktk::DX12Game::deltaTime(), 0.0f });

}
