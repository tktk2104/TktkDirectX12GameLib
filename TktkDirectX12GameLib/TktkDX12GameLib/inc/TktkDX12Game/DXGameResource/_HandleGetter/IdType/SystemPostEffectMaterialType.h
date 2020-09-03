#ifndef SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_
#define SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_

namespace tktk
{
	// システムで使用している通常のポストエフェクトマテリアルの種類
	enum class SystemPostEffectMaterialType
	{
		Monochrome	= 0U,
		Negative,
		SimpleBlur,
		Embossing,
		Sharpness,
		GlassFilter 
	};
}
#endif // !SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_