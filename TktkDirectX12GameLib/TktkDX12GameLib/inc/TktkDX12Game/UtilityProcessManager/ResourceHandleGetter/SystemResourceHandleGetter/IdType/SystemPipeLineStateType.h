#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// システムで使用しているパイプラインステートの種類
	enum class SystemPipeLineStateType
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
		BasicMeshWireFrame,
		BasicMonoColorMesh,
		BasicMonoColorMeshWireFrame
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_