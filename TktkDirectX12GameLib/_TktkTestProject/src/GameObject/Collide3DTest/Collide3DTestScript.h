#ifndef COLLIDE_3D_TEST_SCRIPT_H_
#define COLLIDE_3D_TEST_SCRIPT_H_

#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>

class Collide3DTestScript
	: public tktk::ComponentBase
{
public:

	Collide3DTestScript(float moveSpeed);

public:

	void start();

	void update();

	void onCollisionEnter(const tktk::GameObjectPtr& other);

	void onCollisionStay(const tktk::GameObjectPtr& other);

	void onCollisionExit(const tktk::GameObjectPtr& other);

private:

	float m_moveSpeed;

	tktk::ComponentPtr<tktk::Transform3D> m_transform;
};
#endif // !COLLIDE_3D_TEST_SCRIPT_H_