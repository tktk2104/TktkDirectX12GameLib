#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	// システムで使用しているルートシグネチャの種類
	enum class SystemRootSignatureType
	{
		/* ポストエフェクト */
		PostEffectDrawGameArea,
		PostEffectMonochrome,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,

		/*  */
		Sprite,
		Line2D,
		Billboard,

		/* メッシュ描画 */
		SimpleMesh,
		SkinningMesh,
		InvertSimpleMesh,
		InvertSkinningMesh,
		MonoColorSimpleMesh,
		MonoColorSkinningMesh,

		/* メッシュシャドウマップ描画 */
		SimpleMeshShadowMap,
		SkinningMeshShadowMap,
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_