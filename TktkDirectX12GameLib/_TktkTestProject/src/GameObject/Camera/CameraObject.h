#ifndef CAMERA_OBJECT_H_
#define CAMERA_OBJECT_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/FirstPersonModuleMaker.h>

#include <TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h>

#include <TktkDX12BaseComponents/Components.h>

struct CameraObject
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		gameObject->addGameObjectTag(999);

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		tktk::FirstPersonModuleMaker::makeStart(gameObject)
			.rotateDegSpeedPerSec(30.0f)
			.moveSpeedPerSec(10.0f)
			.enableUpDownKey(true)
			.create();

		tktk::BasicCameraControllerMaker::makeStart(gameObject)
			.initCameraFov(90.0f)
			.create();

		tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
			.initCameraWidth(100.0f)
			.initCameraHeight(100.0f)
			.initCameraHandle(tktk::DX12GameManager::getSystemHandle(tktk::SystemCameraType::DefaultShadowMapCamera))
			.create();

		/*tktk::PointLightControllerMaker::makeStart(gameObject)
			.initDiffuse(tktkMath::Color_v::green)
			.create();*/

		return gameObject;
	}
};
#endif // !CAMERA_OBJECT_H_
