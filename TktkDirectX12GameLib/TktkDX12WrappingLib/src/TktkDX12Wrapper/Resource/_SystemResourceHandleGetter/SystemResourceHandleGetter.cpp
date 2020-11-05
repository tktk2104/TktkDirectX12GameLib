#include "TktkDX12Wrapper/Resource/_SystemResourceHandleGetter/SystemResourceHandleGetter.h"

namespace tktk
{
	size_t SystemResourceHandleGetter::getSystemHandle(SystemViewportType type) const
	{
		return m_systemViewportHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemScissorRectType type) const
	{
		return m_systemScissorRectHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_systemVertexBufferHandleMap.at(type);
	}

	size_t SystemResourceHandleGetter::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_systemIndexBufferHandleMap.at(type);;
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

	void SystemResourceHandleGetter::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_systemViewportHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_systemScissorRectHandleMap.emplace(type, handle);
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
}