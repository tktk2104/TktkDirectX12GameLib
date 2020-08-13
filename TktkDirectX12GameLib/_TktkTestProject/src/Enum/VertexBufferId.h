#ifndef VERTEX_BUFFER_ID_H_
#define VERTEX_BUFFER_ID_H_

#include "ToIntFunc.h"

enum class VertexBufferId
{
	Miku = 0U,
	VertexColorPolygon,

	ElementShapeGuide,
	CollideDebug1,
	CollideDebug2,

	Count
};

constexpr unsigned int VertexBufferNum = static_cast<unsigned int>(VertexBufferId::Count);

#endif // !VERTEX_BUFFER_ID_H_