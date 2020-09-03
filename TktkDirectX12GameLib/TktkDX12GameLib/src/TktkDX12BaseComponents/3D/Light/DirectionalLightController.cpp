#include "TktkDX12BaseComponents/3D/Light/DirectionalLightController.h"

namespace tktk
{
	DirectionalLightController::DirectionalLightController(unsigned int lightHandle, const tktkMath::Vector3& direction, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular)
		: m_lightHandle(lightHandle)
		, m_direction(direction)
		, m_ambient(ambient)
		, m_diffuse(diffuse)
		, m_speqular(speqular)
	{
	}

	void DirectionalLightController::start()
	{
		updateLight();
	}

	void DirectionalLightController::afterCollide()
	{
		updateLight();
	}

	void DirectionalLightController::setDirection(const tktkMath::Vector3& direction)
	{
		m_direction = direction;
	}

	void DirectionalLightController::setAmbient(const tktkMath::Color& ambient)
	{
		m_ambient = ambient;
	}

	void DirectionalLightController::setDiffuse(const tktkMath::Color& diffuse)
	{
		m_diffuse = diffuse;
	}

	void DirectionalLightController::setSpeqular(const tktkMath::Color& speqular)
	{
		m_speqular = speqular;
	}

	void DirectionalLightController::updateLight()
	{
		tktk::DX12GameManager::setLightAmbient(m_lightHandle, m_ambient);
		tktk::DX12GameManager::setLightDiffuse(m_lightHandle, m_diffuse);
		tktk::DX12GameManager::setLightSpeqular(m_lightHandle, m_speqular);

		// TODO : ÇøÇ·ÇÒÇ∆ï˚å¸ÇÃÇ›Ç≈ä«óùÇ∑ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		tktk::DX12GameManager::setLightPosition(m_lightHandle, -m_direction * 10000.0f);
	}
}