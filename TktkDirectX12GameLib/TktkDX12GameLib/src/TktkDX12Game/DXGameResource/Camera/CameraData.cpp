#include "TktkDX12Game/DXGameResource/Camera/CameraData.h"

namespace tktk
{
	const tktkMath::Matrix4& CameraData::getViewMatrix() const
	{
		return m_viewMatrix;
	}

	void CameraData::setViewMatrix(const tktkMath::Matrix4& view)
	{
		m_viewMatrix = view;
	}

	const tktkMath::Matrix4& CameraData::getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	void CameraData::setProjectionMatrix(const tktkMath::Matrix4& projection)
	{
		m_projectionMatrix = projection;
	}
}