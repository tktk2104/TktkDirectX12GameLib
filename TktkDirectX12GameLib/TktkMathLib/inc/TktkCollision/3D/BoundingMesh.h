#ifndef BOUNDING_MESH_H_
#define BOUNDING_MESH_H_

#include <vector>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "Body3DTypeChecker.h"
#include "CollisionSupport3D.h"

namespace tktkCollision
{
	class BoundingMesh
	{
	public:

		BoundingMesh(const std::vector<std::vector<tktkMath::Vector3>>& mesh, const tktkMath::Vector3& centerPos);

	public:

		// 引数のワールド行列で座標変換する
		void transform(const tktkMath::Matrix4& worldMatrix);

		// 球体との衝突判定処理
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

		// メッシュとの衝突判定処理
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

	public:

		const std::vector<std::vector<tktkMath::Vector3>>& getBasePolygonVertex() const;

		const std::vector<std::vector<tktkMath::Vector3>>& getTransformedPolygonVertex() const;

	public:

		// このクラスがメッシュの衝突判定である事の証明
		static constexpr Body3DType ShapeType{ Body3DType::Mesh };

	private:

		// メッシュを構成するポリゴンと、それを構成する頂点
		std::vector<std::vector<tktkMath::Vector3>> m_basePolygonVertex;

		// ワールド空間で座標変換後のメッシュを構成するポリゴンと、それを構成する頂点
		std::vector<std::vector<tktkMath::Vector3>> m_transformedPolygonVertex;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 球体との衝突判定処理
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingMesh::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::meshCollisionWithSphere(m_transformedPolygonVertex, otherBody.getTransformedCenterPosition(), otherBody.getTransformedRadius());
	}

	// メッシュとの衝突判定処理
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingMesh::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::meshCollisionWithMesh(m_transformedPolygonVertex, otherBody.m_transformedPolygonVertex);
	}
}
#endif // !BOUNDING_MESH_H_