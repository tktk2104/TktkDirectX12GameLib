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

		// 引数のワールド行列で座標変換する
		void transform(const tktkMath::Matrix3& worldMatrix);

		// 円との衝突判定処理
		template <class OtherBody2DType, is_BoundingCircle<OtherBody2DType>		= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

		// 二次元ポリゴンとの衝突判定処理
		template <class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType> = nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

	public:

		const std::vector<tktkMath::Vector2>& getVertexs() const;

		const std::vector<tktkMath::Vector2>& getTransformedVertexs() const;

	public:

		// このクラスが二次元ポリゴンの衝突判定である事の証明
		static constexpr Body2DType ShapeType{ Body2DType::Polygon };

	private:

		// ポリゴンを構成する頂点
		std::vector<tktkMath::Vector2> m_baseVertexs;

		// ワールド空間で座標変換後のポリゴンを構成する頂点
		std::vector<tktkMath::Vector2> m_transformedVertexs;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 円との衝突判定処理
	template<class OtherBody2DType, is_BoundingCircle<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::polygonCollisionWithCircle(m_transformedVertexs, otherBody.getTransformedCenterPosition(), otherBody.getTransformedRadius());
	}

	// 二次元ポリゴンとの衝突判定処理
	template<class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>>
	inline HitInfo2D BoundingPolygon2D::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::polygonCollisionWithPolygon(m_transformedVertexs, otherBody.m_transformedVertexs);
	}
}
#endif // !BOUNDING_POLYGON_2D_H_