#ifndef POST_EFFECT_MATERIAL_ID_H_
#define POST_EFFECT_MATERIAL_ID_H_

#include "ToIntFunc.h"

enum class PostEffectMaterialId
{
	PostEffectTest = 0U,

	Count
};

constexpr unsigned int PostEffectMaterialNum = static_cast<unsigned int>(PostEffectMaterialId::Count);

#endif // !POST_EFFECT_MATERIAL_ID_H_