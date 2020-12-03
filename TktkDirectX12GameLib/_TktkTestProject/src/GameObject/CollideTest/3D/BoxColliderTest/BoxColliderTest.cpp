#include "BoxColliderTest.h"

#include "BoxColliderTestScript.h"

tktk::GameObjectPtr BoxColliderTest::create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotate, float moveSpeed, unsigned int collisionGroup, float extrudedRate)
{
	auto gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initRotation(rotate)
		.traceType(tktk::TraceParentType::notTrace)
		.create();

	tktk::BoxColliderMaker::makeStart(gameObject)
		.collisionGroupType(collisionGroup)
		.boxSize({ 1.0f, 1.0f, 1.0f })
		.extrudedRate(extrudedRate)
		.create();

	tktk::ColliderWireFrameDrawer3DMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.lineColor(tktkMath::Color_v::red)
		.create();

	gameObject->createComponent<BoxColliderTestScript>(
		moveSpeed
		);

	return gameObject;
}
