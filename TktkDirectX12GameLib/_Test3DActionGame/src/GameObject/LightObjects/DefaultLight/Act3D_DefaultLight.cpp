#include "Act3D_DefaultLight.h"

tktk::GameObjectPtr Act3D_DefaultLight::create(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation)
{
	// ゲームオブジェクトを作成
	auto gameObject = tktk::DX12Game::createGameObject();

	// ３次元座標コンポーネント
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initRotation(rotation)
		.create();

	// 正射影カメラコンポーネント（シャドウマップを描画するカメラ位置）
	tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
		.initCameraWidth(30.0f)
		.initCameraHeight(30.0f)
		.initCameraHandle(tktk::DX12Game::getSystemHandle(tktk::SystemCameraType::DefaultShadowMapCamera))
		.create();

	// ポイントライトコンポーネント
	tktk::PointLightControllerMaker::makeStart(gameObject)
		.initAmbient({ 0.1f, 1.0f })
		.initSpeqular(tktkMath::Color_v::white)
		.initDiffuse(tktkMath::Color_v::white)
		.create();

	return gameObject;
}
