#ifndef RECT_COLLIDER_TEST_H_
#define RECT_COLLIDER_TEST_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

struct RectColliderTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector2& position, float moveSpeed, unsigned int collisionGroup, float extrudedRate);
};
#endif // !RECT_COLLIDER_TEST_H_