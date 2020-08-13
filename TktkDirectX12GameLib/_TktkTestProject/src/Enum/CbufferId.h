#ifndef CBUFFER_ID_H_
#define CBUFFER_ID_H_

#include "ToIntFunc.h"

enum class CbufferId
{
	VertexColorPolygon = 0U,

	Count
};

constexpr unsigned int CbufferNum = static_cast<unsigned int>(CbufferId::Count);
#endif // !CBUFFER_ID_H_