#include "CircleColliderTest.h"

#include "CircleColliderTestScript.h"

tktk::GameObjectPtr CircleColliderTest::create(const tktkMath::Vector2& position, float moveSpeed, unsigned int collisionGroup, float extrudedRate)
{
	auto gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform2DMaker::makeStart(gameObject)
		.initPosition(position)
		.traceType(tktk::TraceParentType::notTrace)
		.create();

	tktk::CircleColliderMaker::makeStart(gameObject)
		.collisionGroupType(collisionGroup)
		.radius(64.0f)
		.extrudedRate(extrudedRate)
		.create();

	tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.lineColor(tktkMath::Color_v::red)
		.create();

	gameObject->createComponent<CircleColliderTestScript>(
		moveSpeed
		);

	return gameObject;
}
