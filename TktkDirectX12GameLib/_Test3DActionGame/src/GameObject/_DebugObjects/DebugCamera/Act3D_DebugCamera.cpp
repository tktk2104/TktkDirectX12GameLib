#include "Act3D_DebugCamera.h"

tktk::GameObjectPtr Act3D_DebugCamera::create(const tktkMath::Vector3& position)
{
	auto gameObject = tktk::DX12Game::createGameObject();

	// ���W�Ǘ��R���|�[�l���g
	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.create();

	// �ʏ�J�����R���|�[�l���g
	tktk::BasicCameraControllerMaker::makeStart(gameObject)
		.initCameraFov(90.0f)
		.create();

	// �P�l�̈ړ��R���|�[�l���g
	tktk::FirstPersonModuleMaker::makeStart(gameObject)
		.rotateDegSpeedPerSec(30.0f)
		.moveSpeedPerSec(10.0f)
		.enableUpDownKey(true)
		.alwaysMoveForward(false)
		.create();

	return gameObject;
}
