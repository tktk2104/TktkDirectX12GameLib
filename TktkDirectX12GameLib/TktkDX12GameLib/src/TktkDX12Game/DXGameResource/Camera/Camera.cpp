#include "TktkDX12Game/DXGameResource/Camera/Camera.h"

namespace tktk
{
	Camera::Camera(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_cameraArray(initParam)
	{
	}

	unsigned int Camera::create()
	{
		return m_cameraArray.create();
	}

	const tktkMath::Matrix4& Camera::getViewMatrix(unsigned int handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getViewMatrix();
	}

	void Camera::setViewMatrix(unsigned int handle, const tktkMath::Matrix4& view)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setViewMatrix(view);
	}

	const tktkMath::Matrix4& Camera::getProjectionMatrix(unsigned int handle) const
	{
		return m_cameraArray.getMatchHandlePtr(handle)->getProjectionMatrix();
	}

	void Camera::setProjectionMatrix(unsigned int handle, const tktkMath::Matrix4& projection)
	{
		m_cameraArray.getMatchHandlePtr(handle)->setProjectionMatrix(projection);
	}
}