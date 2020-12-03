#ifndef CIRCLE_COLLIDER_TEST_H_
#define CIRCLE_COLLIDER_TEST_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

struct CircleColliderTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float moveSpeed, unsigned int collisionGroup, float extrudedRate);
};
#endif // !CIRCLE_COLLIDER_TEST_H_