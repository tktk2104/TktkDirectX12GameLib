#ifndef SCENE_ID_H_
#define SCENE_ID_H_

#include "ToIntFunc.h"

enum class SceneId
{
	Loading = 0U,
	Main,

	Count
};

constexpr unsigned int SceneNum = static_cast<unsigned int>(SceneId::Count);

#endif // !SCENE_ID_H_