#ifndef POINT_LIGHT_OBJECT_H_
#define POINT_LIGHT_OBJECT_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h>
#include <TktkDX12BaseComponents/3D/Light/PointLightControllerMaker.h>

struct PointLightObject
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.initRotation(tktkMath::Quaternion::createLookRotation(-position))
			.create();

		tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
			.initCameraWidth(40.0f)
			.initCameraHeight(40.0f)
			.initCameraId(1U)
			.create();

		tktk::PointLightControllerMaker::makeStart(gameObject)
			.initLightId(0U)
			.create();

		return gameObject;
	}
};
#endif // !POINT_LIGHT_OBJECT_H_