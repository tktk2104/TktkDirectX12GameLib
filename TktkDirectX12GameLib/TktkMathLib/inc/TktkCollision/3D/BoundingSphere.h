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

		// 引数のワールド行列で座標変換する
		void transform(const tktkMath::Matrix4& worldMatrix);

		// 球体との衝突判定処理
		template <class OtherBody3DType, is_BoundingSphere<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

		// メッシュとの衝突判定処理
		template <class OtherBody3DType, is_BoundingMesh<OtherBody3DType> = nullptr>
		HitInfo3D isCollide(const OtherBody3DType& otherBody) const;

	public:

		// 半径を取得
		float getBaseRadius() const;

		// 中心座標を取得
		const tktkMath::Vector3& getBaseCenterPosition() const;

		// ワールド空間で座標変換後の半径を取得
		float getTransformedRadius() const;

		// ワールド空間で座標変換後の中心座標を取得
		const tktkMath::Vector3& getTransformedCenterPosition() const;

	public:

		// このクラスが球体の衝突判定である事の証明
		static constexpr Body3DType ShapeType{ Body3DType::Sphere };

	private:

		// 球体の半径
		float				m_baseRadius;

		// 球体の中心座標
		tktkMath::Vector3	m_baseCenterPosition;

		// 球体の半径
		float				m_transformedRadius;

		// 球体の中心座標
		tktkMath::Vector3	m_transformedCenterPosition;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 球体との衝突判定処理
	template<class OtherBody3DType, is_BoundingSphere<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::sphereCollisionWithSphere(m_transformedCenterPosition, m_transformedRadius, otherBody.m_transformedCenterPosition, otherBody.m_transformedRadius);
	}
	
	// メッシュとの衝突判定処理
	template<class OtherBody3DType, is_BoundingMesh<OtherBody3DType>>
	inline HitInfo3D BoundingSphere::isCollide(const OtherBody3DType& otherBody) const
	{
		return CollisionSupport3D::sphereCollisionWithMesh(m_transformedCenterPosition, m_transformedRadius, otherBody.getTransformedPolygonVertex());
	}
}
#endif // !BOUNDING_SPHERE_H_