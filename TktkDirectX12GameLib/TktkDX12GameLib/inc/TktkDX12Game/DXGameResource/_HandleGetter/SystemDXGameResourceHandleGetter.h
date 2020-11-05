#ifndef SYSTEM_DX_GAME_RESOURCE_HANDLE_GETTER_H_
#define SYSTEM_DX_GAME_RESOURCE_HANDLE_GETTER_H_

#include <unordered_map>
#include "SystemDXGameResourceType.h"

namespace tktk
{
	class SystemDXGameResourceHandleGetter
	{
	public:

		SystemDXGameResourceHandleGetter() = default;
		~SystemDXGameResourceHandleGetter() = default;

	public:

		size_t getSystemHandle(SystemCameraType type)					const;
		size_t getSystemHandle(SystemLightType type)					const;
		size_t getSystemHandle(SystemBasicMeshType type)				const;
		size_t getSystemHandle(SystemBasicMeshMaterialType type)		const;
		size_t getSystemHandle(SystemPostEffectMaterialType type)		const;

	public:

		void setSystemHandle(SystemCameraType type,				size_t handle);
		void setSystemHandle(SystemLightType type,				size_t handle);
		void setSystemHandle(SystemBasicMeshType type,			size_t handle);
		void setSystemHandle(SystemBasicMeshMaterialType type,	size_t handle);
		void setSystemHandle(SystemPostEffectMaterialType type, size_t handle);

	private:

		std::unordered_map<SystemCameraType,				size_t>	m_systemCameraHandleMap;
		std::unordered_map<SystemLightType,					size_t>	m_systemLightHandleMap;
		std::unordered_map<SystemBasicMeshType,				size_t>	m_systemBasicMeshHandleMap;
		std::unordered_map<SystemBasicMeshMaterialType,		size_t>	m_systemBasicMeshMaterialHandleMap;
		std::unordered_map<SystemPostEffectMaterialType,	size_t>	m_systemPostEffectMaterialHandleMap;
	};
}
#endif // !SYSTEM_DX_GAME_RESOURCE_HANDLE_GETTER_H_