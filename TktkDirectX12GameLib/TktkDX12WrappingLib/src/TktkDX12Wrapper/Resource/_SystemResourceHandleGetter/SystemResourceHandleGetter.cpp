#include "TktkDX12Wrapper/Resource/_SystemResourceHandleGetter/SystemResourceHandleGetter.h"

namespace tktk
{
	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemViewportType type) const
	{
		return m_systemViewportHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemScissorRectType type) const
	{
		return m_systemScissorRectHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_systemVertexBufferHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_systemIndexBufferHandleMap.at(type);;
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemCBufferType type) const
	{
		return m_systemCBufferHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_systemTextureBufferHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemRtBufferType type) const
	{
		return m_systemRtBufferHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemDsBufferType type) const
	{
		return m_systemDsBufferHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_systemBasicDescriptorHeapHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_systemRtvDescriptorHeapHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_systemDsvDescriptorHeapHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_systemRootSignatureHandleMap.at(type);
	}

	unsigned int SystemResourceHandleGetter::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_systemPipeLineStateHandleMap.at(type);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemViewportType type, unsigned int handle)
	{
		m_systemViewportHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemScissorRectType type, unsigned int handle)
	{
		m_systemScissorRectHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemVertexBufferType type, unsigned int handle)
	{
		m_systemVertexBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemIndexBufferType type, unsigned int handle)
	{
		m_systemIndexBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemCBufferType type, unsigned int handle)
	{
		m_systemCBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemTextureBufferType type, unsigned int handle)
	{
		m_systemTextureBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRtBufferType type, unsigned int handle)
	{
		m_systemRtBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemDsBufferType type, unsigned int handle)
	{
		m_systemDsBufferHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemBasicDescriptorHeapType type, unsigned int handle)
	{
		m_systemBasicDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRtvDescriptorHeapType type, unsigned int handle)
	{
		m_systemRtvDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemDsvDescriptorHeapType type, unsigned int handle)
	{
		m_systemDsvDescriptorHeapHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemRootSignatureType type, unsigned int handle)
	{
		m_systemRootSignatureHandleMap.emplace(type, handle);
	}

	void SystemResourceHandleGetter::setSystemHandle(SystemPipeLineStateType type, unsigned int handle)
	{
		m_systemPipeLineStateHandleMap.emplace(type, handle);
	}
}