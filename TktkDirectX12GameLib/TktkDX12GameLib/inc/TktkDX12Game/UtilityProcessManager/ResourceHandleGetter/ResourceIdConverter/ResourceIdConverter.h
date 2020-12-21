#ifndef DX_GAME_RESOURCE_HANDLE_GETTER_H_
#define DX_GAME_RESOURCE_HANDLE_GETTER_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include "ResourceIdCarrier.h"

namespace tktk
{
	// リソースIDをリソースハンドルに変換するクラス
	class ResourceIdConverter
	{
	public:

		ResourceIdConverter() = default;
		~ResourceIdConverter();

	public:

		size_t getSceneHandle					(ResourceIdCarrier id) const;
		size_t getSoundHandle					(ResourceIdCarrier id) const;
		size_t getFontHandle					(ResourceIdCarrier id) const;
		size_t getPostEffectMaterialHandle		(ResourceIdCarrier id) const;
		size_t getSpriteMaterialHandle			(ResourceIdCarrier id) const;
		size_t getLine2DMaterialHandle			(ResourceIdCarrier id) const;
		size_t getBillboardMaterialHandle		(ResourceIdCarrier id) const;
		size_t getSkeletonHandle				(ResourceIdCarrier id) const;
		size_t getMotionHandle					(ResourceIdCarrier id) const;
		size_t getBasicMeshHandle				(ResourceIdCarrier id) const;
		size_t getBasicMeshMaterialHandle		(ResourceIdCarrier id) const;
		size_t getPostEffectDrawFuncRunnerHandle(ResourceIdCarrier id) const;
		size_t getCameraHandle					(ResourceIdCarrier id) const;
		size_t getLightHandle					(ResourceIdCarrier id) const;

	public:

		void setSceneHandle						(ResourceIdCarrier id, size_t handle);
		void setSoundHandle						(ResourceIdCarrier id, size_t handle);
		void setFontHandle						(ResourceIdCarrier id, size_t handle);
		void setPostEffectMaterialHandle		(ResourceIdCarrier id, size_t handle);
		void setSpriteMaterialHandle			(ResourceIdCarrier id, size_t handle);
		void setLine2DMaterialHandle			(ResourceIdCarrier id, size_t handle);
		void setBillboardMaterialHandle			(ResourceIdCarrier id, size_t handle);
		void setSkeletonHandle					(ResourceIdCarrier id, size_t handle);
		void setMotionHandle					(ResourceIdCarrier id, size_t handle);
		void setMeshHandle						(ResourceIdCarrier id, size_t handle);
		void setMeshMaterialHandle				(ResourceIdCarrier id, size_t handle);
		void setPostEffectDrawFuncRunnerHandle	(ResourceIdCarrier id, size_t handle);
		void setCameraHandle					(ResourceIdCarrier id, size_t handle);
		void setLightHandle						(ResourceIdCarrier id, size_t handle);

	private:

		std::unordered_map<ResourceIdCarrier, size_t>	m_sceneHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_soundHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_fontHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_postEffectMaterialHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_spriteMaterialHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_line2DMaterialHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_billboardMaterialHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_skeletonHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_motionHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_basicMeshHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_basicMeshMaterialHandleMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_postEffectDrawFuncRunnerMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_cameraMap;
		std::unordered_map<ResourceIdCarrier, size_t>	m_lightMap;
	};
}
#endif // !DX_GAME_RESOURCE_HANDLE_GETTER_H_