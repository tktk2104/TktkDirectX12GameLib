#ifndef BOX_COLLIDER_TEST_SCRIPT_H_
#define BOX_COLLIDER_TEST_SCRIPT_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

class BoxColliderTestScript
	: public tktk::ComponentBase
{
public:

	explicit BoxColliderTestScript(float moveSpeed);

public:

	void start();

	void update();

	void onCollisionEnter(const tktk::GameObjectPtr& other);

	void onCollisionExit(const tktk::GameObjectPtr& other);

private:

	float m_moveSpeed;

	tktk::ComponentPtr<tktk::Transform3D> m_transform;
};
#endif // !BOX_COLLIDER_TEST_SCRIPT_H_