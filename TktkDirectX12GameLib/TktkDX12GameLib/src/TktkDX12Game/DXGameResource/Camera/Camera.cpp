#include "TktkDX12Game/DXGameResource/Camera/Camera.h"

namespace tktk
{
	Camera::Camera(unsigned int cameraNum)
		: m_cameraArray(cameraNum)
	{
	}

	void Camera::create(unsigned int id)
	{
		m_cameraArray.emplaceAt(id);
	}

	const tktkMath::Matrix4& Camera::getViewMatrix(unsigned int id) const
	{
		return m_cameraArray.at(id)->getViewMatrix();
	}

	void Camera::setViewMatrix(unsigned int id, const tktkMath::Matrix4& view)
	{
		m_cameraArray.at(id)->setViewMatrix(view);
	}

	const tktkMath::Matrix4& Camera::getProjectionMatrix(unsigned int id) const
	{
		return m_cameraArray.at(id)->getProjectionMatrix();
	}

	void Camera::setProjectionMatrix(unsigned int id, const tktkMath::Matrix4& projection)
	{
		m_cameraArray.at(id)->setProjectionMatrix(projection);
	}
}