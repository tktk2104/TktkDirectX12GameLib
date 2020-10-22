#ifndef BODY_3D_TYPE_CHECKER_H_
#define BODY_3D_TYPE_CHECKER_H_

#include <type_traits>
#include "Body3DType.h"

namespace tktkCollision
{
	template<class OtherBody3DType>
	using is_BoundingSphere = std::enable_if_t<OtherBody3DType::ShapeType == Body3DType::Sphere>*;
	template<class OtherBody3DType>
	using is_BoundingMesh	= std::enable_if_t<OtherBody3DType::ShapeType == Body3DType::Mesh>*;
}
#endif // !BODY_3D_TYPE_CHECKER_H_