#ifndef AXIS_ALIGNED_BOUNDING_BOX_H_
#define AXIS_ALIGNED_BOUNDING_BOX_H_

#include "Body3dBase/Body3dBase.h"

namespace tktkCollision
{
	// AABB
	// ※回転は管轄外（回転するならOBBを使おう）
	class AxisAlignedBoundingBox
		: public Body3dBase
	{
	public:

		AxisAlignedBoundingBox(
			const tktkMath::Vector3& boxSize,
			const tktkMath::Vector3& localPosition = tktkMath::Vector3_v::zero
		);

		// 衝突判定
		bool isCollide(const Body3dBase& other, HitInfo3D* hitinfo) const override;

	public:

		// 頂点の種類
		enum class CornerType
		{
			LeftTopFront,
			RightTopFront,
			LeftBottomFront,
			RightBottomFront,

			LeftTopBack,
			RightTopBack,
			LeftBottomBack,
			RightBottomBack,

			Min = LeftBottomFront,
			Max = RightTopBack
		};

		// 頂点座標を計算
		tktkMath::Vector3 calculateCornerPoint(CornerType cornerIndex) const;

		// 当たり判定の大きさを計算
		tktkMath::Vector3 calculateBoxSize() const;

		// ローカルの当たり判定の大きさを計算
		tktkMath::Vector3 calculateLocalBoxSize() const;

	private:

		tktkMath::Vector3 m_boxSize;
	};
}
#endif // !AXIS_ALIGNED_BOUNDING_BOX_H_