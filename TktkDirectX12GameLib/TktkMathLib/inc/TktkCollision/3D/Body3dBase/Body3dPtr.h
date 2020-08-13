#ifndef BODY_3D_PTR_H_
#define BODY_3D_PTR_H_

#include <memory>

namespace tktkCollision
{
	class Body3dBase;
	using Body3dSharedPtr = std::shared_ptr<Body3dBase>;
	using Body3dWeakPtr = std::weak_ptr<Body3dBase>;
}
#endif // !BODY_3D_PTR_H_