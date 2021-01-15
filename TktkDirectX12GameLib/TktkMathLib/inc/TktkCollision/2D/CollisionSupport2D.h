#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

#include <vector>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "HitInfo2D.h"

namespace tktkCollision
{
	class BoundingCircle;
	class BoundingPolygon2D;

	class CollisionSupport2D
	{
	public:

		struct LineCrossCheckResult
		{
			// 線分が交差しているか？
			bool isHit					{ false };

			// 二つの線の交差点
			tktkMath::Vector2 crossPos	{ tktkMath::Vector2_v::zero };
		};

		// ２つの線分が交差しているかと、２つの線の交差点を計算する
		// 交差判定は線分、交差点判定は直線として計算している
		static LineCrossCheckResult lineCrossCheck(
			const tktkMath::Vector2& firstLinePosOne,
			const tktkMath::Vector2& firstLinePosTwo,
			const tktkMath::Vector2& secondLinePosOne,
			const tktkMath::Vector2& secondLinePosTwo
		);

	public:

		struct LinePolygonHitInfo
		{
			// 衝突したかどうか？
			bool							isHit			{ false };

			// ポリゴンと線分の交差点の配列
			std::vector<tktkMath::Vector2>	crossPosArray;
		};

		// “ポリゴン”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const std::vector<tktkMath::Vector2>& otherVertexs);

	public:

		// “円”を使って“円”の衝突判定を行う
		static HitInfo2D circleCollisionWithCircle(const tktkMath::Vector2& selfCenterPos, float selfRadius, const tktkMath::Vector2& otherCenterPos, float otherRadius);

		// “ポリゴン”を使って“ポリゴン”の衝突判定を行う
		static HitInfo2D polygonCollisionWithPolygon(const std::vector<tktkMath::Vector2>& selfVertexs, const std::vector<tktkMath::Vector2>& otherVertexs);

		// “ポリゴン”を使って“円”の衝突判定を行う
		static HitInfo2D circleCollisionWithPolygon(const tktkMath::Vector2& selfCenterPos, float selfRadius, const std::vector<tktkMath::Vector2>& otherVertexs);

		// “円”を使って“ポリゴン”の衝突判定を行う
		static HitInfo2D polygonCollisionWithCircle(const std::vector<tktkMath::Vector2>& selfVertexs, const tktkMath::Vector2& otherCenterPos, float otherRadius);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_