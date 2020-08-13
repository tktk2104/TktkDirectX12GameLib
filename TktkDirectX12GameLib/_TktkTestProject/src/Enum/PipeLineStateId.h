#ifndef PIPE_LINE_STATE_ID_H_
#define PIPE_LINE_STATE_ID_H_

#include "ToIntFunc.h"

enum class PipeLineStateId
{
	VertexColorPolygon = 0U,
	Count
};

constexpr unsigned int PipeLineStateNum = static_cast<unsigned int>(PipeLineStateId::Count);

#endif // !PIPE_LINE_STATE_ID_H_