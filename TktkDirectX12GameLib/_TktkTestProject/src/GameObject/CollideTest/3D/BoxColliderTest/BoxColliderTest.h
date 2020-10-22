#ifndef BOX_COLLIDER_TEST_H_
#define BOX_COLLIDER_TEST_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

struct BoxColliderTest
{
	static tktk::GameObjectPtr create(const tktkMath::Vector3& position, const tktkMath::Vector3& rotate, float moveSpeed, unsigned int collisionGroup, float extrudedRate);
};
#endif // !BOX_COLLIDER_TEST_H_