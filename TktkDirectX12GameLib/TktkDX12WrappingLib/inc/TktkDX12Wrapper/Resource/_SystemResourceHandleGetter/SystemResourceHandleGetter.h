#ifndef SYSTEM_RESOURCE_HANDLE_GETTER_H_
#define SYSTEM_RESOURCE_HANDLE_GETTER_H_

#include <unordered_map>
#include "SystemResourceType.h"

namespace tktk
{
	class SystemResourceHandleGetter
	{
	public:

		SystemResourceHandleGetter() = default;
		~SystemResourceHandleGetter() = default;

	public:

		size_t getSystemHandle(SystemViewportType type)				const;
		size_t getSystemHandle(SystemScissorRectType type)			const;
		size_t getSystemHandle(SystemVertexBufferType type)			const;
		size_t getSystemHandle(SystemIndexBufferType type)			const;
		size_t getSystemHandle(SystemCBufferType type)				const;
		size_t getSystemHandle(SystemTextureBufferType type)		const;
		size_t getSystemHandle(SystemRtBufferType type)				const;
		size_t getSystemHandle(SystemDsBufferType type)				const;
		size_t getSystemHandle(SystemBasicDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemRtvDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemDsvDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemRootSignatureType type)		const;
		size_t getSystemHandle(SystemPipeLineStateType type)		const;

	public:

		void setSystemHandle(SystemViewportType type,				size_t handle);
		void setSystemHandle(SystemScissorRectType type,			size_t handle);
		void setSystemHandle(SystemVertexBufferType type,			size_t handle);
		void setSystemHandle(SystemIndexBufferType type,			size_t handle);
		void setSystemHandle(SystemCBufferType type,				size_t handle);
		void setSystemHandle(SystemTextureBufferType type,			size_t handle);
		void setSystemHandle(SystemRtBufferType type,				size_t handle);
		void setSystemHandle(SystemDsBufferType type,				size_t handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	size_t handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemRootSignatureType type,			size_t handle);
		void setSystemHandle(SystemPipeLineStateType type,			size_t handle);

	private:

		std::unordered_map<SystemViewportType,				size_t>	m_systemViewportHandleMap;
		std::unordered_map<SystemScissorRectType,			size_t>	m_systemScissorRectHandleMap;
		std::unordered_map<SystemVertexBufferType,			size_t>	m_systemVertexBufferHandleMap;
		std::unordered_map<SystemIndexBufferType,			size_t>	m_systemIndexBufferHandleMap;
		std::unordered_map<SystemCBufferType,				size_t>	m_systemCBufferHandleMap;
		std::unordered_map<SystemTextureBufferType,			size_t>	m_systemTextureBufferHandleMap;
		std::unordered_map<SystemRtBufferType,				size_t>	m_systemRtBufferHandleMap;
		std::unordered_map<SystemDsBufferType,				size_t>	m_systemDsBufferHandleMap;
		std::unordered_map<SystemBasicDescriptorHeapType,	size_t>	m_systemBasicDescriptorHeapHandleMap;
		std::unordered_map<SystemRtvDescriptorHeapType,		size_t>	m_systemRtvDescriptorHeapHandleMap;
		std::unordered_map<SystemDsvDescriptorHeapType,		size_t>	m_systemDsvDescriptorHeapHandleMap;
		std::unordered_map<SystemRootSignatureType,			size_t>	m_systemRootSignatureHandleMap;
		std::unordered_map<SystemPipeLineStateType,			size_t>	m_systemPipeLineStateHandleMap;
	};
}
#endif // !SYSTEM_RESOURCE_HANDLE_GETTER_H_
