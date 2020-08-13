#ifndef SPRITE_MATERIAL_ID_H_
#define SPRITE_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class SpriteMaterialId
{
	Test = 0U,

	Count
};

constexpr unsigned int SpriteMaterialNum = static_cast<unsigned int>(SpriteMaterialId::Count);

#endif // !SPRITE_MATERIAL_ID_H_