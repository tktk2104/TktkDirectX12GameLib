#include "TktkDX12Game/DXGameResource/Draw3DParameters/Camera/CameraManager.h"

#include "TktkDX12Game/DXGameResource/Draw3DParameters/Camera/CameraData.h"

namespace tktk
{
	CameraManager::CameraManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_cameraArray(initParam)
	{
	}

	// デストラクタを非インライン化する
	CameraManager::~CameraManager() = default;

	size_t CameraManager::create()
	{
		return m_cameraArray.create();
	}

	const tktkMath::Matrix4& CameraManager::getViewMatrix(size_t handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getViewMatrix();
	}

	void CameraManager::setViewMatrix(size_t handle, const tktkMath::Matrix4& view)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setViewMatrix(view);
	}

	const tktkMath::Matrix4& CameraManager::getProjectionMatrix(size_t handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getProjectionMatrix();
	}

	void CameraManager::setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setProjectionMatrix(projection);
	}
}