#include "Player.h"

#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h>
#include <TktkDX12BaseComponents/3D/Light/PointLightControllerMaker.h>

#include "Scripts/InputToRotate.h"
#include "Scripts/InputToMove.h"

#include "../../../Enum/_ResourceIds/ResourceIds.h"

tktk::GameObjectPtr Player::create(const tktkMath::Vector3 & rotateCenterPos)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(rotateCenterPos)
		.create();

	gameObject->createComponent<InputToRotate>();

	gameObject->addChild(createPlayerCamera());

	return gameObject;
}

tktk::GameObjectPtr Player::createPlayerCamera()
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition({ 0.0f, 0.0f, -10.0f })
		.create();

	tktk::BasicCameraControllerMaker::makeStart(gameObject)
		.initCameraId(CameraId::Basic)
		.initCameraFov(45.0f)
		.initCameraNear(0.1f)
		.initCameraFar(1000.0f)
		.create();

	tktk::PointLightControllerMaker::makeStart(gameObject)
		.initLightId(LightId::Basic)
		.create();

	gameObject->createComponent<InputToMove>();

	return gameObject;
}
