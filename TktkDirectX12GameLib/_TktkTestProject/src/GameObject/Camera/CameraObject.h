#ifndef CAMERA_OBJECT_H_
#define CAMERA_OBJECT_H_

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h>
#include <TktkDX12BaseComponents/3D/Camera/FirstPersonModuleMaker.h>

#include <TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h>

struct CameraObject
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform3DMaker::makeStart(gameObject)
			.initPosition(position)
			.create();

		tktk::FirstPersonModuleMaker::makeStart(gameObject)
			.create();

		tktk::BasicCameraControllerMaker::makeStart(gameObject)
			.initCameraId(0U)
			.initCameraFov(90.0f)
			.create();

		return gameObject;
	}
};
#endif // !CAMERA_OBJECT_H_
