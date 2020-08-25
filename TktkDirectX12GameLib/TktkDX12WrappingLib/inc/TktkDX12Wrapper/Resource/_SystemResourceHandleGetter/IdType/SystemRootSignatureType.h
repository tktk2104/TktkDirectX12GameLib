#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	// システムで使用しているルートシグネチャの数
	constexpr unsigned int SystemRootSignatureNum = 11U;

	// システムで使用しているルートシグネチャの種類
	enum class SystemRootSignatureType
	{
		PostEffectMonochrome	= 0U,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,
		ShadowMap,
		Sprite,
		Line2D,
		BasicMesh,
		BasicMonoColorMesh
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_