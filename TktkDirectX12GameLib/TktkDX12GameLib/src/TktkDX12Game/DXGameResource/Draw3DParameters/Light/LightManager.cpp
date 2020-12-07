#include "TktkDX12Game/DXGameResource/Draw3DParameters/Light/LightManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Draw3DParameters/Light/Structs/LightCBufferData.h"
#include "TktkDX12Game/DXGameResource/Draw3DParameters/Light/LightData.h"

namespace tktk
{
	LightManager::LightManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_lightArray(initParam)
	{
		// ライト用の定数バッファを作る
		DX12GameManager::setSystemHandle(SystemCBufferType::Light, DX12GameManager::createCBuffer(LightCBufferData()));
	}

	// デストラクタを非インライン化する
	LightManager::~LightManager() = default;

	size_t LightManager::create(
		const tktkMath::Color& ambient,
		const tktkMath::Color& diffuse,
		const tktkMath::Color& speqular,
		const tktkMath::Vector3& position
	)
	{
		return m_lightArray.create(ambient, diffuse, speqular, position);
	}

	void LightManager::updateLightCBuffer(size_t handle) const
	{
		m_lightArray.getMatchHandlePtr(handle)->updateLightCBuffer();
	}

	void LightManager::setAmbient(size_t handle, const tktkMath::Color& ambient)
	{
		m_lightArray.getMatchHandlePtr(handle)->setAmbient(ambient);
	}

	void LightManager::setDiffuse(size_t handle, const tktkMath::Color& diffuse)
	{
		m_lightArray.getMatchHandlePtr(handle)->setDiffuse(diffuse);
	}

	void LightManager::setSpeqular(size_t handle, const tktkMath::Color& speqular)
	{
		m_lightArray.getMatchHandlePtr(handle)->setSpeqular(speqular);
	}

	void LightManager::setPosition(size_t handle, const tktkMath::Vector3& position)
	{
		m_lightArray.getMatchHandlePtr(handle)->setPosition(position);
	}
}