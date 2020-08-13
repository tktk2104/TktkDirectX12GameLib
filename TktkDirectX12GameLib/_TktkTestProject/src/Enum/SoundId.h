#ifndef SOUND_ID_H_
#define SOUND_ID_H_

#include "ToIntFunc.h"

enum class SoundId
{
	TestSe = 0U,
	TestBgm,

	Count
};

constexpr unsigned int SoundNum = static_cast<unsigned int>(SoundId::Count);

#endif // !SOUND_ID_H_