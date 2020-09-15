#include "TktkDX12BaseComponents/3D/Light/DirectionalLightController.h"

namespace tktk
{
	DirectionalLightController::DirectionalLightController(unsigned int lightHandle, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular)
		: m_lightHandle(lightHandle)
		, m_ambient(ambient)
		, m_diffuse(diffuse)
		, m_speqular(speqular)
	{
	}

	void DirectionalLightController::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		updateLight();
	}

	void DirectionalLightController::afterCollide()
	{
		updateLight();
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

		auto cameraWorldMat = tktkMath::Matrix4::createTranslation(m_transform->getWorldPosition());

		// TODO : ÇøÇ·ÇÒÇ∆ï˚å¸ÇÃÇ›Ç≈ä«óùÇ∑ÇÈÇÊÇ§Ç…Ç∑ÇÈ
		tktk::DX12GameManager::setLightPosition(m_lightHandle, -cameraWorldMat.calculateForwardLH() * 10000.0f);
	}
}