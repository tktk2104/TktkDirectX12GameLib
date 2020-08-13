#ifndef MOTION_ID_H_
#define MOTION_ID_H_

#include "ToIntFunc.h"

enum class MotionId
{
	motion1 = 0U,
	motion2,

	Count
};

constexpr unsigned int MotionNum = static_cast<unsigned int>(MotionId::Count);

#endif // !MOTION_ID_H_