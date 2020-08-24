#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include "Body3dBase/Body3dBase.h"

namespace tktkCollision
{
	// 球体
// ※楕円体ではない
	class BoundingSphere
		: public Body3dBase
	{
	public:

		BoundingSphere(
			float radius,
			const tktkMath::Vector3& localPosition = tktkMath::Vector3_v::zero
		);

		// 衝突判定
		bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const override;

	public:

		// ※行列のスケールの値はｘ要素だけが使用される
		float calculateRadius() const;

		// ※行列のスケールの値はｘ要素だけが使用される
		float calculateLocalRadius() const;

	private:

		float m_radius;
	};
}
#endif // !BOUNDING_SPHERE_H_