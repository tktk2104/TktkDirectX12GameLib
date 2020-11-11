#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	// システムで使用しているルートシグネチャの種類
	enum class SystemRootSignatureType
	{
		PostEffectMonochrome,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,
		ShadowMap,
		Sprite,
		Line2D,
		Billboard,
		BasicMesh,
		BasicMonoColorMesh
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_