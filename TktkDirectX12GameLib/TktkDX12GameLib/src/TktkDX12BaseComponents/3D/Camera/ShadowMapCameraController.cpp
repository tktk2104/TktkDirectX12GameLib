#include "TktkDX12BaseComponents/3D/Camera/ShadowMapCameraController.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "TktkDX12BaseComponents/3D/Transform3D/Transform3D.h"

namespace tktk
{
	ShadowMapCameraController::ShadowMapCameraController(size_t cameraHandle, GameObjectTagCarrier targetTag, const tktkMath::Vector3& direction, float cameraWidth, float cameraHeight, float cameraNear, float cameraFar)
		: m_cameraHandle(cameraHandle)
		, m_targetTag(targetTag)
		, m_direction(direction)
		, m_cameraWidth(cameraWidth)
		, m_cameraHeight(cameraHeight)
		, m_cameraNear(cameraNear)
		, m_cameraFar(cameraFar)
	{
	}

	void ShadowMapCameraController::afterCollide()
	{
		if (m_targetTransform.expired()) findTargetTransform();

		auto targetPos = tktkMath::Vector3_v::zero;

		if (!m_targetTransform.expired()) targetPos = m_targetTransform->getWorldPosition();

		auto viewMat = tktkMath::Matrix4::createLookAtLH(
			targetPos - (m_direction * (m_cameraFar - m_cameraNear) / 2.0f),
			targetPos,
			tktkMath::Vector3_v::up
		);
		DX12GameManager::setViewMatrix(m_cameraHandle, viewMat);

		auto projectionMat = tktkMath::Matrix4::createOrthographicLH(
			m_cameraWidth,
			m_cameraHeight,
			m_cameraNear,
			m_cameraFar
		);
		DX12GameManager::setProjectionMatrix(m_cameraHandle, projectionMat);
	}

	void ShadowMapCameraController::findTargetTransform()
	{
		auto targetObject = DX12GameManager::findGameObjectWithTag(m_targetTag);

		if (targetObject.expired()) return;

		m_targetTransform = targetObject->getComponent<Transform3D>();
	}
}