#ifndef DX_GAME_RESOURCE_HANDLE_GETTER_H_
#define DX_GAME_RESOURCE_HANDLE_GETTER_H_

#include <unordered_map>

namespace tktk
{
	class DXGameResourceHandleGetter
	{
	public:

		DXGameResourceHandleGetter() = default;
		~DXGameResourceHandleGetter() = default;

	public:

		unsigned int getSceneHandle				(int id) const;
		unsigned int getSoundHandle				(int id) const;
		unsigned int getPostEffectMaterialHandle(int id) const;
		unsigned int getSpriteMaterialHandle	(int id) const;
		unsigned int getLine2DMaterialHandle	(int id) const;
		unsigned int getBillboardMaterialHandle	(int id) const;
		unsigned int getSkeletonHandle			(int id) const;
		unsigned int getMotionHandle			(int id) const;
		unsigned int getBasicMeshHandle			(int id) const;
		unsigned int getBasicMeshMaterialHandle	(int id) const;
		unsigned int getCameraHandle			(int id) const;
		unsigned int getLightHandle				(int id) const;

	public:

		void setSceneHandle				(int id, unsigned int handle);
		void setSoundHandle				(int id, unsigned int handle);
		void setPostEffectMaterialHandle(int id, unsigned int handle);
		void setSpriteMaterialHandle	(int id, unsigned int handle);
		void setLine2DMaterialHandle	(int id, unsigned int handle);
		void setBillboardMaterialHandle	(int id, unsigned int handle);
		void setSkeletonHandle			(int id, unsigned int handle);
		void setMotionHandle			(int id, unsigned int handle);
		void setBasicMeshHandle			(int id, unsigned int handle);
		void setBasicMeshMaterialHandle	(int id, unsigned int handle);
		void setCameraHandle			(int id, unsigned int handle);
		void setLightHandle				(int id, unsigned int handle);

	private:

		std::unordered_map<int, unsigned int>	m_sceneHandleMap;
		std::unordered_map<int, unsigned int>	m_soundHandleMap;
		std::unordered_map<int, unsigned int>	m_postEffectMaterialHandleMap;
		std::unordered_map<int, unsigned int>	m_spriteMaterialHandleMap;
		std::unordered_map<int, unsigned int>	m_line2DMaterialHandleMap;
		std::unordered_map<int, unsigned int>	m_billboardMaterialHandleMap;
		std::unordered_map<int, unsigned int>	m_skeletonHandleMap;
		std::unordered_map<int, unsigned int>	m_motionHandleMap;
		std::unordered_map<int, unsigned int>	m_basicMeshHandleMap;
		std::unordered_map<int, unsigned int>	m_basicMeshMaterialHandleMap;
		std::unordered_map<int, unsigned int>	m_cameraMap;
		std::unordered_map<int, unsigned int>	m_lightMap;
	};
}
#endif // !DX_GAME_RESOURCE_HANDLE_GETTER_H_