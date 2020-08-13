#ifndef SKELETON_ID_H_
#define SKELETON_ID_H_

#include "ToIntFunc.h"

enum class SkeletonId
{
	Miku = 0U,

	Count
};

constexpr unsigned int SkeletonNum = static_cast<unsigned int>(SkeletonId::Count);

#endif // !SKELETON_ID_H_