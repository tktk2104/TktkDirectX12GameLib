#include "RectColliderTest.h"

#include "RectColliderTestScript.h"

tktk::GameObjectPtr RectColliderTest::create(const tktkMath::Vector2& position, float moveSpeed, unsigned int collisionGroup, float extrudedRate)
{
	auto gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform2DMaker::makeStart(gameObject)
		.initPosition(position)
		.traceType(tktk::TraceParentType::notTrace)
		.create();

	tktk::RectColliderMaker::makeStart(gameObject)
		.collisionGroupType(collisionGroup)
		.rectSize({ 128.0f, 128.0f })
		.extrudedRate(extrudedRate)
		.create();

	tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.lineColor(tktkMath::Color_v::red)
		.create();

	gameObject->createComponent<RectColliderTestScript>(
		moveSpeed
		);

	return gameObject;
}
