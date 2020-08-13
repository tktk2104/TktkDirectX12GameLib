#ifndef COLLISION_SUPPORT_3D_H_
#define COLLISION_SUPPORT_3D_H_

#include "HitInfo3D.h"

namespace tktkCollision
{
	class Body3dBase;

	class CollisionSupport3D
	{
	public:

		// 球体と球体の当たり判定
		static bool collideSphereToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo);

		// AABBとAABBの当たり判定
		static bool collideAabbToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo);

		// 球体とAABBの当たり判定
		static bool collideSphereToAabb(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo);

		// AABBと球体の当たり判定（CollideSphereToAabb()の処理を行った後、HitInfoのselfとotherを入れ替える）
		static bool collideAabbToSphere(const Body3dBase& self, const Body3dBase& other, HitInfo3D* hitinfo);
	};
}
#endif // !COLLISION_SUPPORT_3D_H_