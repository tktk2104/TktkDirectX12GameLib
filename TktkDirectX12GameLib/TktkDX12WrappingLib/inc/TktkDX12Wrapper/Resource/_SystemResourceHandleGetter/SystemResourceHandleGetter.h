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

		unsigned int getSystemHandle(SystemViewportType type)				const;
		unsigned int getSystemHandle(SystemScissorRectType type)			const;
		unsigned int getSystemHandle(SystemVertexBufferType type)			const;
		unsigned int getSystemHandle(SystemIndexBufferType type)			const;
		unsigned int getSystemHandle(SystemCBufferType type)				const;
		unsigned int getSystemHandle(SystemTextureBufferType type)			const;
		unsigned int getSystemHandle(SystemRtBufferType type)				const;
		unsigned int getSystemHandle(SystemDsBufferType type)				const;
		unsigned int getSystemHandle(SystemBasicDescriptorHeapType type)	const;
		unsigned int getSystemHandle(SystemRtvDescriptorHeapType type)		const;
		unsigned int getSystemHandle(SystemDsvDescriptorHeapType type)		const;
		unsigned int getSystemHandle(SystemRootSignatureType type)			const;
		unsigned int getSystemHandle(SystemPipeLineStateType type)			const;

	public:

		void setSystemHandle(SystemViewportType type,				unsigned int handle);
		void setSystemHandle(SystemScissorRectType type,			unsigned int handle);
		void setSystemHandle(SystemVertexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemIndexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemCBufferType type,				unsigned int handle);
		void setSystemHandle(SystemTextureBufferType type,			unsigned int handle);
		void setSystemHandle(SystemRtBufferType type,				unsigned int handle);
		void setSystemHandle(SystemDsBufferType type,				unsigned int handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	unsigned int handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemRootSignatureType type,			unsigned int handle);
		void setSystemHandle(SystemPipeLineStateType type,			unsigned int handle);

	private:

		std::unordered_map<SystemViewportType, unsigned int>			m_systemViewportHandleMap;
		std::unordered_map<SystemScissorRectType, unsigned int>			m_systemScissorRectHandleMap;
		std::unordered_map<SystemVertexBufferType, unsigned int>		m_systemVertexBufferHandleMap;
		std::unordered_map<SystemIndexBufferType, unsigned int>			m_systemIndexBufferHandleMap;
		std::unordered_map<SystemCBufferType, unsigned int>				m_systemCBufferHandleMap;
		std::unordered_map<SystemTextureBufferType, unsigned int>		m_systemTextureBufferHandleMap;
		std::unordered_map<SystemRtBufferType, unsigned int>			m_systemRtBufferHandleMap;
		std::unordered_map<SystemDsBufferType, unsigned int>			m_systemDsBufferHandleMap;
		std::unordered_map<SystemBasicDescriptorHeapType, unsigned int> m_systemBasicDescriptorHeapHandleMap;
		std::unordered_map<SystemRtvDescriptorHeapType, unsigned int>	m_systemRtvDescriptorHeapHandleMap;
		std::unordered_map<SystemDsvDescriptorHeapType, unsigned int>	m_systemDsvDescriptorHeapHandleMap;
		std::unordered_map<SystemRootSignatureType, unsigned int>		m_systemRootSignatureHandleMap;
		std::unordered_map<SystemPipeLineStateType, unsigned int>		m_systemPipeLineStateHandleMap;
	};
}
#endif // !SYSTEM_RESOURCE_HANDLE_GETTER_H_
