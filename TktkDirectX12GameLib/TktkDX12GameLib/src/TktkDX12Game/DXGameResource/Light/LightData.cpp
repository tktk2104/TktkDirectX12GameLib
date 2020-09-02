#include "TktkDX12Game/DXGameResource/Light/LightData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	LightData::LightData(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
		: m_lightCBuffer({ ambient, diffuse, speqular, position })
	{
		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyBufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Light), LightCBuffer());
	}

	LightData::~LightData()
	{
		DX12GameManager::eraseCopyBuffer(m_createCopyBufferHandle);
	}

	LightData::LightData(LightData&& other) noexcept
		: m_lightCBuffer(other.m_lightCBuffer)
		, m_createCopyBufferHandle(other.m_createCopyBufferHandle)
	{
		other.m_createCopyBufferHandle = 0U;
	}

	void LightData::updateLightCBuffer() const
	{
		updateCopyBuffer();

		DX12GameManager::copyBuffer(m_createCopyBufferHandle);
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

	void LightData::updateCopyBuffer() const
	{
		tktk::DX12GameManager::updateCopyBuffer(m_createCopyBufferHandle, m_lightCBuffer);
	}
}