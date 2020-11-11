#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���p�C�v���C���X�e�[�g�̎��
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