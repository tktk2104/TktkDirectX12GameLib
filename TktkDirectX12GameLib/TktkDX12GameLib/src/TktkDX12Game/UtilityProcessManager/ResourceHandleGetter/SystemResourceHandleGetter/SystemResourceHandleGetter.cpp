#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/SystemResourceHandleGetter.h"

namespace tktk
{
	// デストラクタを非インライン化する
	SystemResourceHandleGetter::~SystemResourceHandleGetter() = default;

	size_t SystemResourceHandleGetter::getSystemHandle(SystemViewportType type) const
	{
		return m_systemViewportHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemScissorRectType type) const
	{
		return m_systemScissorRectHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemUploadBufferType type) const
	{
		return m_systemUploadBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_systemVertexBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_systemIndexBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemCBufferType type) const
	{
		return m_systemCBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_systemTextureBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemRtBufferType type) const
	{
		return m_systemRtBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemDsBufferType type) const
	{
		return m_systemDsBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_systemBasicDescriptorHeapHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_systemRtvDescriptorHeapHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_systemDsvDescriptorHeapHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_systemRootSignatureHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_systemPipeLineStateHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemSpriteType type) const
	{
		return m_systemSpriteHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemCameraType type) const
	{
		return m_systemCameraHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemLightType type) const
	{
		return m_systemLightHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemMeshType type) const
	{
		return m_systemBasicMeshHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemMeshMaterialType type) const
	{
		return m_systemBasicMeshMaterialHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemPostEffectMaterialType type) const
	{
		return m_systemPostEffectMaterialHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemPostEffectDrawFuncRunnerType type) const
	{
		return m_systemPostEffectDrawFuncRunnerHandleMap.at(type);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_systemViewportHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_systemScissorRectHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemUploadBufferType type, size_t handle)
	{
		m_systemUploadBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemVertexBufferType type, size_t handle)
	{
		m_systemVertexBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemIndexBufferType type, size_t handle)
	{
		m_systemIndexBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemCBufferType type, size_t handle)
	{
		m_systemCBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemTextureBufferType type, size_t handle)
	{
		m_systemTextureBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRtBufferType type, size_t handle)
	{
		m_systemRtBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemDsBufferType type, size_t handle)
	{
		m_systemDsBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
	{
		m_systemBasicDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
	{
		m_systemRtvDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
	{
		m_systemDsvDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRootSignatureType type, size_t handle)
	{
		m_systemRootSignatureHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemPipeLineStateType type, size_t handle)
	{
		m_systemPipeLineStateHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemSpriteType type, size_t handle)
	{
		m_systemSpriteHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemCameraType type, size_t handle)
	{
		m_systemCameraHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemLightType type, size_t handle)
	{
		m_systemLightHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemMeshType type, size_t handle)
	{
		m_systemBasicMeshHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemMeshMaterialType type, size_t handle)
	{
		m_systemBasicMeshMaterialHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
	{
		m_systemPostEffectMaterialHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemPostEffectDrawFuncRunnerType type, size_t handle)
	{
		m_systemPostEffectDrawFuncRunnerHandleMap.emplace(type, handle);
	}
}