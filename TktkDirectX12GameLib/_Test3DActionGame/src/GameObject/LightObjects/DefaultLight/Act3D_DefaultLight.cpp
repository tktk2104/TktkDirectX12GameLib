#include "Act3D_DefaultLight.h"

tktk::GameObjectPtr Act3D_DefaultLight::create(const tktkMath::Vector3& position, const tktkMath::Quaternion& rotation)
{
	// �Q�[���I�u�W�F�N�g���쐬
	auto gameObject = tktk::DX12Game::createGameObject();

	// �R�������W�R���|�[�l���g
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initRotation(rotation)
		.create();

	// ���ˉe�J�����R���|�[�l���g�i�V���h�E�}�b�v��`�悷��J�����ʒu�j
	tktk::OrthographicCameraControllerMaker::makeStart(gameObject)
		.initCameraWidth(30.0f)
		.initCameraHeight(30.0f)
		.initCameraHandle(tktk::DX12Game::getSystemHandle(tktk::SystemCameraType::DefaultShadowMapCamera))
		.create();

	// �|�C���g���C�g�R���|�[�l���g
	tktk::PointLightControllerMaker::makeStart(gameObject)
		.initAmbient({ 0.1f, 1.0f })
		.initSpeqular(tktkMath::Color_v::white)
		.initDiffuse(tktkMath::Color_v::white)
		.create();

	return gameObject;
}
