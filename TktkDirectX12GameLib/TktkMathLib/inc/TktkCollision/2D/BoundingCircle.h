#ifndef BOUNDING_CIRCLE_H_
#define BOUNDING_CIRCLE_H_

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>
#include "Body2DTypeChecker.h"
#include "CollisionSupport2D.h"

namespace tktkCollision
{
	// 円の衝突判定のクラス
	// ※ｙのスケール値は無視される
	class BoundingCircle
	{
	public:

		BoundingCircle(float radius, const tktkMath::Vector2& centerPosition);

	public:

		// 引数のワールド行列で座標変換する
		void transform(const tktkMath::Matrix3& worldMatrix);

		// 円との衝突判定処理
		template <class OtherBody2DType, is_BoundingCircle<OtherBody2DType>		= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

		// 二次元ポリゴンとの衝突判定処理
		template <class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>	= nullptr>
		HitInfo2D isCollide(const OtherBody2DType& otherBody) const;

	public:

		// 半径を取得
		float getRadius() const;

		// 中心座標を取得
		const tktkMath::Vector2& getCenterPosition() const;

		// ワールド空間で座標変換後の半径を取得
		float getTransformedRadius() const;

		// ワールド空間で座標変換後の中心座標を取得
		const tktkMath::Vector2& getTransformedCenterPosition() const;

	public:

		// このクラスが円の衝突判定である事の証明
		static constexpr Body2DType ShapeType{ Body2DType::Circle };

	private:

		// 円の半径
		float				m_baseRadius;

		// 円の中心座標
		tktkMath::Vector2	m_baseCenterPosition;

		// 円の半径
		float				m_transformedRadius;

		// 円の中心座標
		tktkMath::Vector2	m_transformedCenterPosition;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下はテンプレート関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 円との衝突判定処理
	template<class OtherBody2DType, is_BoundingCircle<OtherBody2DType>>
	inline HitInfo2D BoundingCircle::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::circleCollisionWithCircle(m_transformedCenterPosition, m_transformedRadius, otherBody.m_transformedCenterPosition, otherBody.m_transformedRadius);
	}

	// 二次元ポリゴンとの衝突判定処理
	template<class OtherBody2DType, is_BoundingPolygon2d<OtherBody2DType>>
	inline HitInfo2D BoundingCircle::isCollide(const OtherBody2DType& otherBody) const
	{
		return CollisionSupport2D::circleCollisionWithPolygon(m_transformedCenterPosition, m_transformedRadius, otherBody.getTransformedVertexs());
	}
}
#endif // !BOUNDING_CIRCLE_H_