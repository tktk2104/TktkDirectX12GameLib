#include "Act3D_DefaultLight.h"

tktk::GameObjectPtr Act3D_DefaultLight::create(const tktkMath::Vector3& position)
{
	// ゲームオブジェクトを作成
	auto gameObject = tktk::DX12Game::createGameObject();

	// ３次元座標コンポーネント
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.create();

	// ポイントライトコンポーネント
	tktk::PointLightControllerMaker::makeStart(gameObject)
		.initAmbient({ 0.1f, 1.0f })
		.initSpeqular(tktkMath::Color_v::white)
		.initDiffuse(tktkMath::Color_v::white)
		.create();

	return gameObject;
}