#ifndef BODY_2D_TYPE_CHECKER_H_
#define BODY_2D_TYPE_CHECKER_H_

#include <type_traits>
#include "Body2DType.h"

namespace tktkCollision
{
	template<class OtherBody3DType>
	using is_BoundingCircle		= std::enable_if_t<OtherBody3DType::ShapeType == Body2DType::Circle>*;
	template<class OtherBody3DType>
	using is_BoundingPolygon2d	= std::enable_if_t<OtherBody3DType::ShapeType == Body2DType::Polygon>*;
}
#endif // !BODY_2D_TYPE_CHECKER_H_