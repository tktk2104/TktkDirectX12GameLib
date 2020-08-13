#include "TktkDX12Game/DXGameResource/Light/Light.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	Light::Light(unsigned int lightNum)
		: m_lightArray(lightNum)
	{
		// ライト用の定数バッファを作る
		tktk::DX12GameManager::createCBuffer(tktk::DX12GameManager::getSystemId(tktk::SystemCBufferType::Light), LightCBuffer());
	}

	void Light::create(
		unsigned int id,
		const tktkMath::Color& ambient,
		const tktkMath::Color& diffuse,
		const tktkMath::Color& speqular,
		const tktkMath::Vector3& position
	)
	{
		m_lightArray.emplaceAt(
			id,
			ambient,
			diffuse,
			speqular,
			position
		);
	}

	void Light::updateLightCBuffer(unsigned int id) const
	{
		m_lightArray.at(id)->updateLightCBuffer();
	}

	void Light::setAmbient(unsigned int id, const tktkMath::Color& ambient)
	{
		m_lightArray.at(id)->setAmbient(ambient);
	}

	void Light::setDiffuse(unsigned int id, const tktkMath::Color& diffuse)
	{
		m_lightArray.at(id)->setDiffuse(diffuse);
	}

	void Light::setSpeqular(unsigned int id, const tktkMath::Color& speqular)
	{
		m_lightArray.at(id)->setSpeqular(speqular);
	}

	void Light::setPosition(unsigned int id, const tktkMath::Vector3& position)
	{
		m_lightArray.at(id)->setPosition(position);
	}
}