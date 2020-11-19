#ifndef RESOUSE_HANDLE_GETTER_H_
#define RESOUSE_HANDLE_GETTER_H_

/* std::unique_ptr */
#include <memory>

/* class member */
#include "SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "SystemResourceHandleGetter/IdType/SystemBasicMeshType.h"
#include "SystemResourceHandleGetter/IdType/SystemBasicMeshMaterialType.h"
#include "SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	class SystemResourceHandleGetter;
	class ResourceIdConverter;

	// リソースを表すハンドルを取得するクラス
	class ResourceHandleGetter
	{
	public:

		ResourceHandleGetter();
		~ResourceHandleGetter();

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
		size_t getSystemHandle(SystemMeshType type)			const;
		size_t getSystemHandle(SystemMeshMaterialType type)	const;
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
		void setSystemHandle(SystemMeshType type,				size_t handle);
		void setSystemHandle(SystemMeshMaterialType type,		size_t handle);
		void setSystemHandle(SystemPostEffectMaterialType type,		size_t handle);

	public:

		size_t getSceneHandle				(ResourceIdCarrier id) const;
		size_t getSoundHandle				(ResourceIdCarrier id) const;
		size_t getPostEffectMaterialHandle	(ResourceIdCarrier id) const;
		size_t getSpriteMaterialHandle		(ResourceIdCarrier id) const;
		size_t getLine2DMaterialHandle		(ResourceIdCarrier id) const;
		size_t getBillboardMaterialHandle	(ResourceIdCarrier id) const;
		size_t getSkeletonHandle			(ResourceIdCarrier id) const;
		size_t getMotionHandle				(ResourceIdCarrier id) const;
		size_t getBasicMeshHandle			(ResourceIdCarrier id) const;
		size_t getBasicMeshMaterialHandle	(ResourceIdCarrier id) const;
		size_t getCameraHandle				(ResourceIdCarrier id) const;
		size_t getLightHandle				(ResourceIdCarrier id) const;

	public:

		void setSceneHandle				(ResourceIdCarrier id, size_t handle);
		void setSoundHandle				(ResourceIdCarrier id, size_t handle);
		void setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle);
		void setSpriteMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setLine2DMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setBillboardMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setSkeletonHandle			(ResourceIdCarrier id, size_t handle);
		void setMotionHandle			(ResourceIdCarrier id, size_t handle);
		void setMeshHandle			(ResourceIdCarrier id, size_t handle);
		void setMeshMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setCameraHandle			(ResourceIdCarrier id, size_t handle);
		void setLightHandle				(ResourceIdCarrier id, size_t handle);

	private:

		std::unique_ptr<SystemResourceHandleGetter> m_systemResouseHandleGetter;
		std::unique_ptr<ResourceIdConverter>		m_resourceIdConverter;
	};
}
#endif // !RESOUSE_HANDLE_GETTER_H_