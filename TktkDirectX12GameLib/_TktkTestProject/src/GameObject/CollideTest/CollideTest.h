#ifndef COLLIDE_TEST_H_
#define COLLIDE_TEST_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h>
#include <TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h>
#include <TktkDX12BaseComponents/2D/CircleCollider/CircleColliderMaker.h>
#include <TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h>

#include "../../Enum/_ResourceIds/ResourceIds.h"
#include "CollideTestScript.h"

struct CollideTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float moveSpeed, unsigned int collisionGroup, Line2DMaterialId id)
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::Transform2DMaker::makeStart(gameObject)
			.initPosition(position)
			.traceType(tktk::TraceParentType::notTrace)
			.create();

		tktk::SpriteDrawerMaker::makeStart(gameObject)
			.drawPriority(0.5f)
			.spriteMaterialId(TextureBufferId::Test)
			.create();

		tktk::CircleColliderMaker::makeStart(gameObject)
			.collisionGroupType(collisionGroup)
			.radius(128.0f)
			.create();

		tktk::ColliderWireFrameDrawer2DMaker::makeStart(gameObject)
			.drawPriority(0.0f)
			.useLine2DMaterialIdArray({ toInt(id) })
			.lineColor(tktkMath::Color_v::red)
			.create();

		gameObject->createComponent<CollideTestScript>(
			moveSpeed
			);

		return gameObject;
	}
};
#endif // !COLLIDE_TEST_H_