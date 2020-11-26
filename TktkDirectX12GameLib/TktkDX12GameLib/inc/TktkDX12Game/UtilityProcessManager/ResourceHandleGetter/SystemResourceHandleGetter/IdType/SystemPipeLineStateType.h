#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// システムで使用しているパイプラインステートの種類
	enum class SystemPipeLineStateType
	{
		/* ポストエフェクト */
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
		BillboardEffect,

		/* メッシュ描画 */
		SimpleMesh,
		SkinningMesh,
		InvertSimpleMesh,
		InvertSkinningMesh,
		MonoColorSimpleMesh,
		MonoColorSkinningMesh,
		MonoColorSimpleMeshWireFrame,
		MonoColorSkinningMeshWireFrame,

		/* メッシュシャドウマップ描画 */
		SimpleMeshShadowMap,
		SkinningMeshShadowMap,
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_