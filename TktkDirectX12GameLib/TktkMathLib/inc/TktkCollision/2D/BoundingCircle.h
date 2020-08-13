#ifndef BOUNDING_CIRCLE_H_
#define BOUNDING_CIRCLE_H_

#include "Body2dBase/Body2dBase.h"

class BoundingCircle
	: public Body2dBase
{
public:

	BoundingCircle(
		float radius,
		const tktkMath::Vector2& localPosition = tktkMath::vec2Zero
	);

	bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

public:

	// ※行列のスケールの値はｘ要素だけが使用される
	float calculateRadius() const;

	// ※行列のスケールの値はｘ要素だけが使用される
	float calculateLocalRadius() const;

private:

	float m_radius;
};

#endif // !BOUNDING_CIRCLE_H_