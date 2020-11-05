#include "TktkDX12Game/DXGameResource/_HandleGetter/SystemDXGameResourceHandleGetter.h"

namespace tktk
{
	size_t SystemDXGameResourceHandleGetter::getSystemHandle(SystemCameraType type) const
	{
		return m_systemCameraHandleMap.at(type);
	}

	size_t SystemDXGameResourceHandleGetter::getSystemHandle(SystemLightType type) const
	{
		return m_systemLightHandleMap.at(type);
	}

	size_t SystemDXGameResourceHandleGetter::getSystemHandle(SystemBasicMeshType type) const
	{
		return m_systemBasicMeshHandleMap.at(type);
	}

	size_t SystemDXGameResourceHandleGetter::getSystemHandle(SystemBasicMeshMaterialType type) const
	{
		return m_systemBasicMeshMaterialHandleMap.at(type);
	}

	size_t SystemDXGameResourceHandleGetter::getSystemHandle(SystemPostEffectMaterialType type) const
	{
		return m_systemPostEffectMaterialHandleMap.at(type);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemCameraType type, size_t handle)
	{
		m_systemCameraHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemLightType type, size_t handle)
	{
		m_systemLightHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemBasicMeshType type, size_t handle)
	{
		m_systemBasicMeshHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemBasicMeshMaterialType type, size_t handle)
	{
		m_systemBasicMeshMaterialHandleMap.emplace(type, handle);
	}

	void SystemDXGameResourceHandleGetter::setSystemHandle(SystemPostEffectMaterialType type, size_t handle)
	{
		m_systemPostEffectMaterialHandleMap.emplace(type, handle);
	}
}