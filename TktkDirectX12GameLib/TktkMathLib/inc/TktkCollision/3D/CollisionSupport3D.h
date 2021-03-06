#ifndef COLLISION_SUPPORT_3D_H_
#define COLLISION_SUPPORT_3D_H_

#include <array>
#include <vector>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "HitInfo3D.h"

namespace tktkCollision
{
	class BoundingSphere;
	class BoundingMesh;

	class CollisionSupport3D
	{
	public:

		struct LinePolygonHitInfo
		{
			// ポリゴンと線分が“衝突”したかどうか？
			bool				isHit				{ false };

			// ポリゴンの“延長面上に”線分が“衝突”したかどうか？
			bool				isExtensionPolyHit	{ false };

			// ポリゴンの“辺上に”線分が“衝突”したかどうか？
			bool				isPolyEdgeHit		{ false };

			// ポリゴンの“延長面上に”線分が“交差”したかどうか？
			bool				isExtensionPolyCross{ false };

			// 線とポリゴンの衝突点
			tktkMath::Vector3	hitPos				{ tktkMath::Vector3_v::zero };
		};

		// “ポリゴン”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<tktkMath::Vector3>& otherPolygon);

	public:

		// “メッシュ”を使って“点”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static bool pointCollisionWithMesh(const tktkMath::Vector3& point, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// 線とポリゴンの衝突情報
		struct LinePolyHitData
		{
			// 線とポリゴンが交差しているか？
			bool								isCross			{ false };

			// 線とポリゴンの辺が衝突しているか？
			bool								isPolyEdgeHit	{ false };

			// 線とポリゴンの衝突点
			tktkMath::Vector3					hitPos			{ tktkMath::Vector3_v::zero };

			// 交差したポリゴンの頂点
			std::vector<tktkMath::Vector3>		polyVert		{};
		};

		struct LineMeshHitInfo
		{
			// 衝突したかどうか？
			bool								isHit{ false };

			// 線とメッシュの交差点（基本１つだが、線が貫通していたりすると複数の結果となる）
			std::vector<LinePolyHitData>		linePolyCrossDataArray;
		};

		// “メッシュ”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LineMeshHitInfo lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// “メッシュ”を使って“ポリゴン”の衝突判定を行う
		static HitInfo3D polygonCollisionWithMesh(const std::vector<tktkMath::Vector3>& polygon, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

	public:

		// “球体”を使って“球体”の衝突判定を行う
		static HitInfo3D sphereCollisionWithSphere(const tktkMath::Vector3& selfCenterPos, float selfRadius, const tktkMath::Vector3& otherCenterPos, float otherRadius);

		// “メッシュ”を使って“メッシュ”の衝突判定を行う
		static HitInfo3D meshCollisionWithMesh(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

		// “メッシュ”を使って“球体”の衝突判定を行う
		static HitInfo3D sphereCollisionWithMesh(const tktkMath::Vector3& selfCenterPos, float selfRadius, const std::vector<std::vector<tktkMath::Vector3>>& otherMesh);

		// “球体”を使って“メッシュ”の衝突判定を行う
		static HitInfo3D meshCollisionWithSphere(const std::vector<std::vector<tktkMath::Vector3>>& selfMesh, const tktkMath::Vector3& otherCenterPos, float otherRadius);
	};
}
#endif // !COLLISION_SUPPORT_3D_H_