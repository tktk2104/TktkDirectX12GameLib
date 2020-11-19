#include "Act3D_DebugCamera.h"

tktk::GameObjectPtr Act3D_DebugCamera::create(const tktkMath::Vector3& position)
{
	auto gameObject = tktk::DX12Game::createGameObject();

	// 座標管理コンポーネント
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.create();

	// 通常カメラコンポーネント
	tktk::BasicCameraControllerMaker::makeStart(gameObject)
		.initCameraFov(90.0f)
		.create();

	// １人称移動コンポーネント
	tktk::FirstPersonModuleMaker::makeStart(gameObject)
		.rotateDegSpeedPerSec(30.0f)
		.moveSpeedPerSec(10.0f)
		.enableUpDownKey(true)
		.alwaysMoveForward(false)
		.create();

	return gameObject;
}
