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
			// 衝突したかどうか？
			bool				isHit{ false };

			// 線とポリゴンの交差点
			tktkMath::Vector3	crossPos{ tktkMath::Vector3_v::zero };
		};

		// “ポリゴン”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LinePolygonHitInfo lineCollisionWithPolygon(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const std::array<tktkMath::Vector3, 3U>& otherVertexs);

	public:

		struct LineMeshHitInfo
		{
			// 衝突したかどうか？
			bool								isHit{ false };

			// 線とポリゴンの交差点
			tktkMath::Vector3					crossPos{ tktkMath::Vector3_v::zero };

			// 押し出しに使用したポリゴンを構成する頂点座標
			std::array<tktkMath::Vector3, 3U>	otherVertexs{ tktkMath::Vector3_v::zero, tktkMath::Vector3_v::zero, tktkMath::Vector3_v::zero };
		};

		// “メッシュ”を使って“線”の衝突判定を行う
		// ※衝突判定結果の形式が他と違う
		static LineMeshHitInfo lineCollisionWithMesh(const tktkMath::Vector3& firstPos, const tktkMath::Vector3& secondPos, const BoundingMesh& otherBody, const tktkMath::Matrix4& otherWorldMatrix);

	public:

		// “球体”を使って“球体”の衝突判定を行う
		static HitInfo3D sphereCollisionWithSphere(const BoundingSphere& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// “メッシュ”を使って“メッシュ”の衝突判定を行う
		static HitInfo3D meshCollisionWithMesh(const BoundingMesh& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// “メッシュ”を使って“球体”の衝突判定を行う
		static HitInfo3D sphereCollisionWithMesh(const BoundingSphere& selfBody, const BoundingMesh& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);

		// “球体”を使って“メッシュ”の衝突判定を行う
		static HitInfo3D meshCollisionWithSphere(const BoundingMesh& selfBody, const BoundingSphere& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix);
	};
}
#endif // !COLLISION_SUPPORT_3D_H_