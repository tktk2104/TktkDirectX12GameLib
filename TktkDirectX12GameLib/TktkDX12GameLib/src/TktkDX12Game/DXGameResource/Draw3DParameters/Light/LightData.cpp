#include "TktkDX12Game/DXGameResource/Draw3DParameters/Light/LightData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	LightData::LightData(const tktkMath::Color& ambient, const tktkMath::Color& diffuse, const tktkMath::Color& speqular, const tktkMath::Vector3& position)
		: m_lightCBuffer({ ambient, diffuse, speqular, position })
	{
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Light), LightCBuffer()));
	}

	LightData::~LightData()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	LightData::LightData(LightData&& other) noexcept
		: m_lightCBuffer(other.m_lightCBuffer)
		, m_createUploadBufferHandle(other.m_createUploadBufferHandle)
	{
		other.m_createUploadBufferHandle = 0U;
	}

	void LightData::updateLightCBuffer() const
	{
		updateCopyBuffer();

		DX12GameManager::copyBuffer(m_createUploadBufferHandle);
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
		tktk::DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, m_lightCBuffer);
	}
}