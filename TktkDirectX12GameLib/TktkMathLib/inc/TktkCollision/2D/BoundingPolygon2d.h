#ifndef BOUNDING_POLYGON_2D_H_
#define BOUNDING_POLYGON_2D_H_

#include <vector>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "Body2DTypeChecker.h"
#include "CollisionSupport2D.h"

namespace tktkCollision
{
	class BoundingPolygon2D
	{
	public:

		explicit BoundingPolygon2D(const std::vector<tktkMath::Vector2>& vertexs);

	public:

		// 円との衝突判定処理
		template <class OtherBody2DType, is_BoundingCircle<OtherBody2DType>		= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix) const;

		// 二次元ポリゴンとの衝突判定処理
		template <class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType> = nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix) const;

	public:

		const std::vector<tktkMath::Vector2>& getVertexs() const;

	public:

		// このクラスが二次元ポリゴンの衝突判定である事の証明
		static constexpr Body2DType ShapeType{ Body2DType::Polygon };

	private:

		// ポリゴンを構成する頂点
		std::vector<tktkMath::Vector2> m_vertexs;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 円との衝突判定処理
	template<class OtherBody2DType, is_BoundingCircle<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix) const
	{
		return CollisionSupport2D::polygonCollisionWithCircle(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}

	// 二次元ポリゴンとの衝突判定処理
	template<class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody, const tktkMath::Matrix3& selfWorldMatrix, const tktkMath::Matrix3& otherWorldMatrix) const
	{
		return CollisionSupport2D::polygonCollisionWithPolygon(*this, otherBody, selfWorldMatrix, otherWorldMatrix);
	}
}
#endif // !BOUNDING_POLYGON_2D_H_