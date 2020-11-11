#ifndef SYSTEM_RESOUSE_HANDLE_GETTER_H_
#define SYSTEM_RESOUSE_HANDLE_GETTER_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include "IdType/SystemViewportType.h"
#include "IdType/SystemScissorRectType.h"
#include "IdType/SystemVertexBufferType.h"
#include "IdType/SystemIndexBufferType.h"
#include "IdType/SystemConstantBufferType.h"
#include "IdType/SystemTextureBufferType.h"
#include "IdType/SystemRenderTargetBufferType.h"
#include "IdType/SystemDepthStencilBufferType.h"
#include "IdType/SystemBasicDescriptorHeapType.h"
#include "IdType/SystemRtvDescriptorHeapType.h"
#include "IdType/SystemDsvDescriptorHeapType.h"
#include "IdType/SystemRootSignatureType.h"
#include "IdType/SystemPipeLineStateType.h"
#include "IdType/SystemCameraType.h"
#include "IdType/SystemLightType.h"
#include "IdType/SystemBasicMeshType.h"
#include "IdType/SystemBasicMeshMaterialType.h"
#include "IdType/SystemPostEffectMaterialType.h"

namespace tktk
{
	// システムで使用しているリソースのハンドルを取得するクラス
	class SystemResourceHandleGetter
	{
	public:

		SystemResourceHandleGetter() = default;
		~SystemResourceHandleGetter();

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
		size_t getSystemHandle(SystemCameraType type)				const;
		size_t getSystemHandle(SystemLightType type)				const;
		size_t getSystemHandle(SystemBasicMeshType type)			const;
		size_t getSystemHandle(SystemBasicMeshMaterialType type)	const;
		size_t getSystemHandle(SystemPostEffectMaterialType type)	const;

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
		void setSystemHandle(SystemCameraType type,					size_t handle);
		void setSystemHandle(SystemLightType type,					size_t handle);
		void setSystemHandle(SystemBasicMeshType type,				size_t handle);
		void setSystemHandle(SystemBasicMeshMaterialType type,		size_t handle);
		void setSystemHandle(SystemPostEffectMaterialType type,		size_t handle);

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
		std::unordered_map<SystemCameraType,				size_t>	m_systemCameraHandleMap;
		std::unordered_map<SystemLightType,					size_t>	m_systemLightHandleMap;
		std::unordered_map<SystemBasicMeshType,				size_t>	m_systemBasicMeshHandleMap;
		std::unordered_map<SystemBasicMeshMaterialType,		size_t>	m_systemBasicMeshMaterialHandleMap;
		std::unordered_map<SystemPostEffectMaterialType,	size_t>	m_systemPostEffectMaterialHandleMap;
	};
}
#endif // !SYSTEM_RESOUSE_HANDLE_GETTER_H_