#ifndef LIGHT_ID_H_
#define LIGHT_ID_H_

#include "ToIntFunc.h"

enum class LightId
{
	Basic = 0U,

	Count
};

constexpr unsigned int LightNum = static_cast<unsigned int>(LightId::Count);

#endif // !LIGHT_ID_H_