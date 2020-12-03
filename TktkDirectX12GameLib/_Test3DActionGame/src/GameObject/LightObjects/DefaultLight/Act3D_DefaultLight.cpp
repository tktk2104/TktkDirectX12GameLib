#include "Act3D_DefaultLight.h"

tktk::GameObjectPtr Act3D_DefaultLight::create(const tktkMath::Vector3& position)
{
	// �Q�[���I�u�W�F�N�g���쐬
	auto gameObject = tktk::DX12Game::createGameObject();

	// �R�������W�R���|�[�l���g
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.create();

	// �|�C���g���C�g�R���|�[�l���g
	tktk::PointLightControllerMaker::makeStart(gameObject)
		.initAmbient({ 0.1f, 1.0f })
		.initSpeqular(tktkMath::Color_v::white)
		.initDiffuse(tktkMath::Color_v::white)
		.create();

	return gameObject;
}