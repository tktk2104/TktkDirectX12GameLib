#ifndef POINT_LIGHT_OBJECT_H_
#define POINT_LIGHT_OBJECT_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h>
#include <TktkDX12BaseComponents/3D/Light/DirectionalLightControllerMaker.h>

struct DirectionalLightObject
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.initRotation(tktkMath::Quaternion::createLookRotation(-position))
			.create();

		tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
			.initCameraWidth(100.0f)
			.initCameraHeight(100.0f)
			.initCameraHandle(tktk::DX12GameManager::getSystemHandle(tktk::SystemCameraType::DefaultShadowMapCamera))
			.create();

		tktk::DirectionalLightControllerMaker::makeStart(gameObject)
			.create();

		return gameObject;
	}
};
#endif // !POINT_LIGHT_OBJECT_H_