#include "TktkDX12BaseComponents/3D/Camera/BasicCameraController.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicCameraController::BasicCameraController(
		size_t cameraHandle,
		float camerafov,
		float cameraAspect,
		float cameraNear,
		float cameraFar
	)
		: m_cameraHandle(cameraHandle)
		, m_cameraFov(camerafov)
		, m_cameraAspect(cameraAspect)
		, m_cameraNear(cameraNear)
		, m_cameraFar(cameraFar)
	{
	}

	void BasicCameraController::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BasicMeshDrawer not found Transform3D");
		}

		updateCameraMat();
	}

	void BasicCameraController::afterCollide()
	{
		updateCameraMat();
	}

	void BasicCameraController::updateCameraMat()
	{
		auto cameraWorldMat = m_transform->calculateWorldMatrix();

		auto viewMat = tktkMath::Matrix4::createLookAtLH(
			m_transform->getWorldPosition(),
			m_transform->getWorldPosition() + cameraWorldMat.calculateForwardLH(),
			cameraWorldMat.calculateUp()
		);
		DX12GameManager::setViewMatrix(m_cameraHandle, viewMat);

		auto projectionMat = tktkMath::Matrix4::createPerspectiveFieldOfViewLH(
			m_cameraFov,
			m_cameraAspect,
			m_cameraNear,
			m_cameraFar
		);
		DX12GameManager::setProjectionMatrix(m_cameraHandle, projectionMat);
	}
}