#ifndef MIKU_SCRIPT_H_
#define MIKU_SCRIPT_H_

#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/3D/Transform3D/Transform3D.h>

class MikuScript
	: public tktk::ComponentBase
{
public:

	MikuScript() = default;

public:

	void start();

	void awake();

	void onEnable();

	void onDisable();

	void onDestroy();

	void update();

	void afterCollide();

	bool isCollide(const tktk::ComponentBasePtr& other);

	void onCollisionEnter(const tktk::GameObjectPtr& other);

	void onCollisionStay(const tktk::GameObjectPtr& other);

	void onCollisionExit(const tktk::GameObjectPtr& other);

private:

	tktk::ComponentPtr<tktk::Transform3D> m_transform;
};
#endif // !MIKU_SCRIPT_H_
