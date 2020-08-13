#ifndef TEXTURE_ID_H_
#define TEXTURE_ID_H_

#include "ToIntFunc.h"

enum class TextureBufferId
{
	Test = 0U,
	MikuTexStart,
	MikuTexEnd = MikuTexStart + 17U,

	Count
};

constexpr unsigned int TextureBufferNum = static_cast<unsigned int>(TextureBufferId::Count);

#endif // !TEXTURE_ID_H_