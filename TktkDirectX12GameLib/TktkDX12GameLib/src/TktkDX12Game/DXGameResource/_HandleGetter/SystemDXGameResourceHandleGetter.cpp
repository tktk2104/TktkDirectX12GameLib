#include "TktkDX12Game/DXGameResource/_HandleGetter/SystemDXGameResourceHandleGetter.h"

namespace tktk
{
	unsigned int SystemDXGameResourceHandleGetter::getSystemHandle(SystemCameraType type) const
	{
		return m_systemCameraHandleMap.at(type);
	}

	unsigned int SystemDXGameResourceHandleGetter::getSystemHandle(SystemLightType type) const
	{
		return m_systemLightHandleMap.at(type);
	}

	unsigned int SystemDXGameResourceHandleGetter::getSystemHandle(SystemBasicMeshType type) const
	{
		return m_systemBasicMeshHandleMap.at(type);
	}

	unsigned int SystemDXGameResourceHandleGetter::getSystemHandle(SystemBasicMeshMaterialType type) const
	{
		return m_systemBasicMeshMaterialHandleMap.at(type);
	}

	unsigned int SystemDXGameResourceHandleGetter::getSystemHandle(SystemPostEffectMaterialType type) const
	{
		return m_systemPostEffectMaterialHandleMap.at(type);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemCameraType type, unsigned int handle)
	{
		m_systemCameraHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemLightType type, unsigned int handle)
	{
		m_systemLightHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemBasicMeshType type, unsigned int handle)
	{
		m_systemBasicMeshHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemBasicMeshMaterialType type, unsigned int handle)
	{
		m_systemBasicMeshMaterialHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemPostEffectMaterialType type, unsigned int handle)
	{
		m_systemPostEffectMaterialHandleMap.emplace(type, handle);
	}
}