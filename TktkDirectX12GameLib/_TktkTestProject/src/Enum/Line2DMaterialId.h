#ifndef LINE_2D_MATERIAL_ID_H_
#define LINE_2D_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class Line2DMaterialId
{
	ElementShapeGuide = 0U,

	Count
};

constexpr unsigned int line2DMaterialNum = static_cast<unsigned int>(Line2DMaterialId::Count);

#endif // !LINE_2D_MATERIAL_ID_H_