#include "TktkDX12Game/DXGameResource/Light/LightData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	LightData::LightData(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
		: m_lightCBuffer({ ambient, diffuse, speqular, position })
	{
	}

	LightData::LightData(LightData&& other) noexcept
		: m_lightCBuffer(other.m_lightCBuffer)
	{
	}

	void LightData::updateLightCBuffer() const
	{
		tktk::DX12GameManager::updateCBuffer(tktk::DX12GameManager::getSystemHandle(tktk::SystemCBufferType::Light), m_lightCBuffer);
	}

	void LightData::setAmbient(const tktkMath::Color& ambient)
	{
		m_lightCBuffer.lightAmbient = ambient;
	}

	void LightData::setDiffuse(const tktkMath::Color& diffuse)
	{
		m_lightCBuffer.lightDiffuse = diffuse;
	}

	void LightData::setSpeqular(const tktkMath::Color& speqular)
	{
		m_lightCBuffer.lightSpeqular = speqular;
	}

	void LightData::setPosition(const tktkMath::Vector3& position)
	{
		m_lightCBuffer.lightPosition = position;
	}
}