#include "MainScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/CollideTest/CollideTest.h"
#include "../GameObject/Collide3DTest/Collide3DTest.h"
#include "../GameObject/Cursor/Cursor.h"
#include "../GameObject/Miku/Miku.h"
#include "../GameObject/SphereTest/SphereTest.h"
#include "../GameObject/Camera/CameraObject.h"
#include "../GameObject/Light/PointLightObject.h"
#include "../GameObject/Light/DirectionalLightObject.h"
#include "../GameObject/PostEffectObject/PostEffectObject.h"
#include "../GameObject/BillboardTest/BillboardTest.h"

//#include "../TutorialCode/GameObject/Player/Player.h"
//#include "../TutorialCode/GameObject/Enemy/Enemy.h"
//#include "../TutorialCode/GameObject/ElementSphereManager/ElementSphereManager.h"

void MainScene::start()
{
	
	/*tktk::DX12GameManager::playSound(0U, false);
	tktk::DX12GameManager::playSound(1U, true);*/
	
	DirectionalLightObject::create({ 0.0f, 0.0f, -50.0f });
	CameraObject::create({ 0.0f, 16.0f, -20.0f });
	

	//BillboardTest::create(tktkMath::Vector3_v::zero);

	Cursor::create();
	Miku::create(tktkMath::Vector3_v::zero);
	//SphereTest::create(tktkMath::Vector3_v::zero);

	/*for (size_t i = 0; i < 5; i++)
	{
		Miku::create(tktkMath::Vector3(10.0f * i, 0.0f, 0.0f));
	}*/


	PostEffectObject::create();
	

	/*Collide3DTest::create({ 0.0f, 0.0f, -10.0f }, 0.1f, 1);
	Collide3DTest::create({ 0.0f, 0.0f, 10.0f }, 0.2f, 2);*/

	/*CollideTest::create({ 0.0f, 0.0f }, 10.0f, 1, Line2DMaterialId::CollideDebug1);

	CollideTest::create({ 300.0f, 300.0f }, 3.0f, 2, Line2DMaterialId::CollideDebug2);*/

	/*Player::create(tktkMath::Vector3_v::zero);
	Enemy::create(tktkMath::Vector3_v::zero);
	ElementSphereManager::create();*/
}

void MainScene::end()
{
}
