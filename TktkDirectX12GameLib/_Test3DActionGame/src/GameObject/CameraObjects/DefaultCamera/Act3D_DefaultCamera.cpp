#include "Act3D_DefaultCamera.h"

#include "../../../Enums/Enums.h"
#include "../../SkyBox/Act3D_SkyBox.h"

tktk::GameObjectPtr Act3D_DefaultCamera::create(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation)
{
	auto gameObject = tktk::DX12Game::createGameObject();

	// 座標管理コンポーネント
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initRotation(rotation)
		.create();

	// 通常カメラコンポーネント
	tktk::BasicCameraControllerMaker::makeStart(gameObject)
		.initCameraFov(90.0f)
		.create();

	// シャドウマップカメラコンポーネント
	tktk::ShadowMapCameraControllerMaker::makeStart(gameObject)
		.direction({ 0.0f, -1.0f, 1.0f })
		.initCameraWidth(50.0f)
		.initCameraHeight(50.0f)
		.initCameraNear(0.0f)
		.initCameraFar(100.0f)
		.targetTag(GameObjectTag::Player)
		.create();

	gameObject->addChild(Act3D_SkyBox::create());

	return gameObject;
}
