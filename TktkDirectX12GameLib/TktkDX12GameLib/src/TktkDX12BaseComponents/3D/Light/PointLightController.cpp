#include "TktkDX12BaseComponents/3D/Light/PointLightController.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PointLightController::PointLightController(size_t lightHandle, const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular)
		: m_lightHandle(lightHandle)
		, m_ambient(ambient)
		, m_diffuse(diffuse)
		, m_speqular(speqular)
	{
	}

	void PointLightController::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		updateLight();
	}

	void PointLightController::afterCollide()
	{
		updateLight();
	}

	void PointLightController::setAmbient(const tktkMath::Color& ambient)
	{
		m_ambient = ambient;
	}

	void PointLightController::setDiffuse(const tktkMath::Color& diffuse)
	{
		m_diffuse = diffuse;
	}

	void PointLightController::setSpeqular(const tktkMath::Color& speqular)
	{
		m_speqular = speqular;
	}

	void PointLightController::updateLight()
	{
		auto cameraWorldMat = m_transform->calculateWorldMatrix();

		tktk::DX12GameManager::setLightAmbient(m_lightHandle,	m_ambient);
		tktk::DX12GameManager::setLightDiffuse(m_lightHandle,	m_diffuse);
		tktk::DX12GameManager::setLightSpeqular(m_lightHandle,	m_speqular);
		tktk::DX12GameManager::setLightPosition(m_lightHandle,	cameraWorldMat.calculateTranslation());
	}
}