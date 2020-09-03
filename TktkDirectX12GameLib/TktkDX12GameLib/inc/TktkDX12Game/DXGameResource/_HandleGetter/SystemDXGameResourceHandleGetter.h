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

		unsigned int getSystemHandle(SystemCameraType type)					const;
		unsigned int getSystemHandle(SystemLightType type)					const;
		unsigned int getSystemHandle(SystemBasicMeshType type)				const;
		unsigned int getSystemHandle(SystemBasicMeshMaterialType type)		const;
		unsigned int getSystemHandle(SystemPostEffectMaterialType type)		const;

	public:

		void setSystemHandle(SystemCameraType type,				unsigned int handle);
		void setSystemHandle(SystemLightType type,				unsigned int handle);
		void setSystemHandle(SystemBasicMeshType type,			unsigned int handle);
		void setSystemHandle(SystemBasicMeshMaterialType type,	unsigned int handle);
		void setSystemHandle(SystemPostEffectMaterialType type, unsigned int handle);

	private:

		std::unordered_map<SystemCameraType, unsigned int>				m_systemCameraHandleMap;
		std::unordered_map<SystemLightType, unsigned int>				m_systemLightHandleMap;
		std::unordered_map<SystemBasicMeshType, unsigned int>			m_systemBasicMeshHandleMap;
		std::unordered_map<SystemBasicMeshMaterialType, unsigned int>	m_systemBasicMeshMaterialHandleMap;
		std::unordered_map<SystemPostEffectMaterialType, unsigned int>	m_systemPostEffectMaterialHandleMap;
	};
}
#endif // !SYSTEM_DX_GAME_RESOURCE_HANDLE_GETTER_H_