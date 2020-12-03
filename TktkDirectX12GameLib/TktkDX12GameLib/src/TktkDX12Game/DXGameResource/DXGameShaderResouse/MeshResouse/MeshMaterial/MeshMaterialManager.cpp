#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialManager.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialData.h"

namespace tktk
{
	MeshMaterialManager::MeshMaterialManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_basicMeshMaterialArray(initParam)
	{
	}

	// デストラクタを非インライン化する
	MeshMaterialManager::~MeshMaterialManager() = default;

	size_t MeshMaterialManager::create(const MeshMaterialInitParam& initParam)
	{
		return m_basicMeshMaterialArray.create(initParam);
	}

	size_t MeshMaterialManager::copy(size_t originalHandle)
	{
		return m_basicMeshMaterialArray.create(*m_basicMeshMaterialArray.getMatchHandlePtr(originalHandle));
	}

	void MeshMaterialManager::setMaterialData(size_t handle) const
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.getMatchHandlePtr(handle);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->setMaterialData();
	}

	void MeshMaterialManager::addAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.getMatchHandlePtr(handle);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->addAppendParam(initParam);
	}

	void MeshMaterialManager::updateAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.getMatchHandlePtr(handle);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->updateAppendParam(updateFuncArgs);
	}
}