#ifndef BOUNDING_RECT_H_
#define BOUNDING_RECT_H_

#include "Body2dBase/Body2dBase.h"

class BoundingRect
	: public Body2dBase
{
public:

	BoundingRect(
		const tktkMath::Vector2& rectSize,
		const tktkMath::Vector2& localPosition = tktkMath::Vector2_v::zero
	);

	bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

public:

	// 頂点の種類
	enum class CornerType
	{
		LeftTop,
		RightTop,
		LeftBottom,
		RightBottom,

		Min = LeftTop,
		Max = RightBottom
	};

public:

	// 頂点座標を計算
	tktkMath::Vector2 calculateCornerPoint(CornerType cornerIndex) const;

	// 当たり判定の大きさを計算
	tktkMath::Vector2 calculateRectSize() const;

private:

	tktkMath::Vector2 m_rectSize;
};

#endif // !BOUNDING_RECT_H_