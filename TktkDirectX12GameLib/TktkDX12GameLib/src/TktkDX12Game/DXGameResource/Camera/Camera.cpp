#include "TktkDX12Game/DXGameResource/Camera/Camera.h"

namespace tktk
{
	Camera::Camera(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_cameraArray(initParam)
	{
	}

	size_t Camera::create()
	{
		return m_cameraArray.create();
	}

	const tktkMath::Matrix4& Camera::getViewMatrix(size_t handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getViewMatrix();
	}

	void Camera::setViewMatrix(size_t handle, const tktkMath::Matrix4& view)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setViewMatrix(view);
	}

	const tktkMath::Matrix4& Camera::getProjectionMatrix(size_t handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getProjectionMatrix();
	}

	void Camera::setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setProjectionMatrix(projection);
	}
}