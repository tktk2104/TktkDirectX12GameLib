#include "MainScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/CollideTest/CollideTest.h"
#include "../GameObject/Collide3DTest/Collide3DTest.h"
#include "../GameObject/Cursor/Cursor.h"
#include "../GameObject/Miku/Miku.h"
#include "../GameObject/SphereTest/SphereTest.h"
#include "../GameObject/Camera/CameraObject.h"
#include "../GameObject/Light/PointLightObject.h"
#include "../GameObject/PostEffectObject/PostEffectObject.h"

#include "../TutorialCode/GameObject/Player/Player.h"
#include "../TutorialCode/GameObject/Enemy/Enemy.h"
#include "../TutorialCode/GameObject/ElementSphereManager/ElementSphereManager.h"

void MainScene::start()
{
	/*x
	tktk::DX12GameManager::playSound(0U, false);
	tktk::DX12GameManager::playSound(1U, true);
	Cursor::create();
	CameraObject::create({ 0.0f, 16.0f, -20.0f });
	PointLightObject::create({ 60.0f, 10.0f, -60.0f });
	Miku::create(tktkMath::Vector3_v::zero);
	SphereTest::create(tktkMath::Vector3_v::zero);
	PostEffectObject::create();
	*/

	Collide3DTest::create({ 0.0f, 0.0f, -2.0f }, 1.0f, 1);
	Collide3DTest::create({ 0.0f, 0.0f, 2.0f }, 3.0f, 2);

	/*CollideTest::create({ 0.0f, 0.0f }, 10.0f, 1, Line2DMaterialId::CollideDebug1);

	CollideTest::create({ 300.0f, 300.0f }, 3.0f, 2, Line2DMaterialId::CollideDebug2);*/

	Player::create(tktkMath::Vector3_v::zero);
	Enemy::create(tktkMath::Vector3_v::zero);
	ElementSphereManager::create();
}

void MainScene::end()
{
}
