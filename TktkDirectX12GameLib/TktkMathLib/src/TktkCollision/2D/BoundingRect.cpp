#include "TktkCollision/2D/BoundingRect.h"

#include "TktkCollision/2D/Body2dBase/CollisionSupport2D.h"

namespace tktkCollision
{
	BoundingRect::BoundingRect(
		const tktkMath::Vector2& rectSize,
		const tktkMath::Vector2& localPosition
	)
		: Body2dBase(
			ShapeType2D::Rect,
			tktkMath::Matrix3::createTranslation(localPosition)
		)
		, m_rectSize(rectSize)
	{
	}

	bool BoundingRect::isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const
	{
		switch (other.getShapeType())
		{
		case ShapeType2D::Circle:

			return CollisionSupport2D::collideRectToCircle(*this, other, hitinfo);

		case ShapeType2D::Rect:

			return CollisionSupport2D::collideRectToRect(*this, other, hitinfo);

		case ShapeType2D::Polygon:

			return CollisionSupport2D::collideRectToPolygon(*this, other, hitinfo);
		}
		return false;
	}

	tktkMath::Vector2 BoundingRect::calculateCornerPoint(CornerType cornerIndex) const
	{
		tktkMath::Vector2 worldRectSize = calculateRectSize();

		tktkMath::Vector2 cornerLocalPosition;

		switch (cornerIndex)
		{
		case CornerType::LeftTop:		cornerLocalPosition = tktkMath::Vector2(-worldRectSize.x / 2, -worldRectSize.y / 2); break;
		case CornerType::RightTop:		cornerLocalPosition = tktkMath::Vector2(worldRectSize.x / 2, -worldRectSize.y / 2); break;
		case CornerType::LeftBottom:	cornerLocalPosition = tktkMath::Vector2(-worldRectSize.x / 2, worldRectSize.y / 2); break;
		case CornerType::RightBottom:	cornerLocalPosition = tktkMath::Vector2(worldRectSize.x / 2, worldRectSize.y / 2); break;
		}
		return calculatePose().calculateTranslation() + cornerLocalPosition;
	}

	tktkMath::Vector2 BoundingRect::calculateRectSize() const
	{
		auto selfPose = calculatePose();

		// スケールのみを使用したワールド行列を作成する
		auto ignoreRotateWorldMatrix = tktkMath::Matrix3::createScale(selfPose.calculateScale()) * tktkMath::Matrix3::createTranslation(selfPose.calculateTranslation());

		return (tktkMath::Matrix3::createScale(m_rectSize) * ignoreRotateWorldMatrix).calculateScale();
	}
}