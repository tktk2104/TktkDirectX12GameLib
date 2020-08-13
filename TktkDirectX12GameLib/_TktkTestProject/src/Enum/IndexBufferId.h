#ifndef INDEX_BUFFER_ID_H_
#define INDEX_BUFFER_ID_H_

#include "ToIntFunc.h"

enum class IndexBufferId
{
	Miku = 0U,
	VertexColorPolygon,

	Count
};

constexpr unsigned int IndexBufferNum = static_cast<unsigned int>(IndexBufferId::Count);

#endif // !INDEX_BUFFER_ID_H_