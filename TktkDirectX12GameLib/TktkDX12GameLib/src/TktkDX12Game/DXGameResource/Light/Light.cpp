#include "TktkDX12Game/DXGameResource/Light/Light.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	Light::Light(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_lightArray(initParam)
	{
		// ライト用の定数バッファを作る
		DX12GameManager::setSystemHandle(SystemCBufferType::Light, DX12GameManager::createCBuffer(LightCBuffer()));
	}

	unsigned int Light::create(
		const tktkMath::Color& ambient,
		const tktkMath::Color& diffuse,
		const tktkMath::Color& speqular,
		const tktkMath::Vector3& position
	)
	{
		return m_lightArray.create(ambient, diffuse, speqular, position);
	}

	void Light::updateLightCBuffer(unsigned int handle) const
	{
		m_lightArray.getMatchHandlePtr(handle)->updateLightCBuffer();
	}

	void Light::setAmbient(unsigned int handle, const tktkMath::Color& ambient)
	{
		m_lightArray.getMatchHandlePtr(handle)->setAmbient(ambient);
	}

	void Light::setDiffuse(unsigned int handle, const tktkMath::Color& diffuse)
	{
		m_lightArray.getMatchHandlePtr(handle)->setDiffuse(diffuse);
	}

	void Light::setSpeqular(unsigned int handle, const tktkMath::Color& speqular)
	{
		m_lightArray.getMatchHandlePtr(handle)->setSpeqular(speqular);
	}

	void Light::setPosition(unsigned int handle, const tktkMath::Vector3& position)
	{
		m_lightArray.getMatchHandlePtr(handle)->setPosition(position);
	}
}