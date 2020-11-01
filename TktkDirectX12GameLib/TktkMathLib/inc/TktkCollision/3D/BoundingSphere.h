#ifndef BOUNDING_SPHERE_H_
#define BOUNDING_SPHERE_H_

#include "Body3DTypeChecker.h"
#include "CollisionSupport3D.h"

namespace tktkCollision
{
	// 球体
	// ※ｙ、ｚのスケール値は無視される
	class BoundingSphere
	{
	public:

		BoundingSphere(float radius, const tktkMath::Vector3& centerPosition);

	public:

		// 球体との衝突判定処理
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

		// メッシュとの衝突判定処理
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const;

	public:

		// 半径を取得
		float getRadius() const;

		// 中心座標を取得
		const tktkMath::Vector3& getCenterPosition() const;

	public:

		// このクラスが球体の衝突判定である事の証明
		static constexpr Body3DType ShapeType{ Body3DType::Sphere };

	private:

		// 球体の半径
		float				m_radius;

		// 球体の中心座標
		tktkMath::Vector3	m_centerPosition;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 球体との衝突判定処理
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::sphereCollisionWithSphere(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
	
	// メッシュとの衝突判定処理
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody, const tktkMath::Matrix4& selfWorldMatrix, const tktkMath::Matrix4& otherWorldMatrix) const
	{
		return CollisionSupport3D::sphereCollisionWithMesh(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
}
#endif // !BOUNDING_SPHERE_H_