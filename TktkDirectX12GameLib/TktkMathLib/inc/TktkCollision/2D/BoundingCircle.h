#ifndef BOUNDING_CIRCLE_H_
#define BOUNDING_CIRCLE_H_

#include "Body2dBase/Body2dBase.h"

namespace tktkCollision
{
	class BoundingCircle
		: public Body2dBase
	{
	public:

		BoundingCircle(
			float radius,
			const tktkMath::Vector2& localPosition = tktkMath::Vector2_v::zero
		);

		bool isCollide(const Body2dBase& other, HitInfo2D* hitinfo) const override;

	public:

		// ���s��̃X�P�[���̒l�͂��v�f�������g�p�����
		float calculateRadius() const;

		// ���s��̃X�P�[���̒l�͂��v�f�������g�p�����
		float calculateLocalRadius() const;

	private:

		float m_radius;
	};
}
#endif // !BOUNDING_CIRCLE_H_