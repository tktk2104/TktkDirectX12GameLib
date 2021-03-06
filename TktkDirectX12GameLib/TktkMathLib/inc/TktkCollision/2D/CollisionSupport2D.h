#ifndef COLLISION_SUPPORT_2D_H_
#define COLLISION_SUPPORT_2D_H_

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

		// ポリゴンとポリゴンの当たり判定
		static bool collidePolygonToPolygon(const BoundingPolygon2D& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// 円とポリゴンの当たり判定
		static bool collideCircleToPolygon(const BoundingCircle& selfBody, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// ポリゴンと点の当たり判定
		static bool collidePolygonToPoint(const BoundingPolygon2D& selfBody, const tktkMath::Vector2& otherPoint, const tktkMath::Matrix3& selfWorldMatrix);
	
	public:

		struct LineCrossCheckResult
		{
			// 線分が交差しているか？
			bool isHit{ false };

			// 二つの線の交差点
			tktkMath::Vector2 crossPos{ tktkMath::Vector2_v::zero };
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
			bool				isHit				{ false };

			// 衝突時“線”を“線の終了座標を基準に開始座標方向に押し出す”時の線の終了座標
			tktkMath::Vector2	selfExtrudePos		{ tktkMath::Vector2_v::zero };

			// 押し出しに使用したポリゴンの辺を構成する１つ目の頂点座標
			tktkMath::Vector2	hitLineFirstVert	{ tktkMath::Vector2_v::zero };

			// 押し出しに使用したポリゴンの辺を構成する２つ目の頂点座標
			tktkMath::Vector2	hitLineSecondVert	{ tktkMath::Vector2_v::zero };
		};

		// “ポリゴン”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector2& firstPos, const tktkMath::Vector2& secondPos, const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& otherWorldMatrix);


	public:

		// “円”を使って“円”の衝突判定を行う
		static HitInfo2D circleCollisionWithCircle(const BoundingCircle& selfBody,		const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// “ポリゴン”を使って“ポリゴン”の衝突判定を行う
		static HitInfo2D polygonCollisionWithPolygon(const BoundingPolygon2D& selfBody,	const BoundingPolygon2D& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// “ポリゴン”を使って“円”の衝突判定を行う
		static HitInfo2D circleCollisionWithPolygon(const BoundingCircle& selfBody,		const BoundingPolygon2D& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);

		// “円”を使って“ポリゴン”の衝突判定を行う
		static HitInfo2D polygonCollisionWithCircle(const BoundingPolygon2D& selfBody,	const BoundingCircle& otherBody,	const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix);
	};
}
#endif // !COLLISION_SUPPORT_2D_H_