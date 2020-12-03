#ifndef RECT_COLLIDER_TEST_SCRIPT_H_
#define RECT_COLLIDER_TEST_SCRIPT_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

class RectColliderTestScript
	: public tktk::ComponentBase
{
public:

	explicit RectColliderTestScript(float moveSpeed);

public:

	void start();

	void update();

	void onCollisionEnter(const tktk::GameObjectPtr& other);

	void onCollisionExit(const tktk::GameObjectPtr& other);

private:

	float m_moveSpeed;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !RECT_COLLIDER_TEST_SCRIPT_H_