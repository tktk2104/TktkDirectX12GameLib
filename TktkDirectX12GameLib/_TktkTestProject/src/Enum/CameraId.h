#ifndef CAMERA_ID_H_
#define CAMERA_ID_H_

#include "ToIntFunc.h"

enum class CameraId
{
	Basic = 0U,
	ShadowMap,

	Count
};

constexpr unsigned int CameraNum = static_cast<unsigned int>(CameraId::Count);

#endif // !CAMERA_ID_H_