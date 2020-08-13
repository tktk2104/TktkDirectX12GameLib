#ifndef COLLIDE_TEST_SCRIPT_H_
#define COLLIDE_TEST_SCRIPT_H_

#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2D.h>

class CollideTestScript
	: public tktk::ComponentBase
{
public:

	CollideTestScript(float moveSpeed);

public:

	void start();

	void update();

	void onCollisionEnter(const tktk::GameObjectPtr& other);

	void onCollisionStay(const tktk::GameObjectPtr& other);

	void onCollisionExit(const tktk::GameObjectPtr& other);

private:

	float m_moveSpeed;

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};

#endif // !COLLIDE_TEST_SCRIPT_H_