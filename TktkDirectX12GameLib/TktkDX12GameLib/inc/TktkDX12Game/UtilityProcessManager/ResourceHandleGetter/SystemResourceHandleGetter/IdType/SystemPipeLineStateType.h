#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���p�C�v���C���X�e�[�g�̎��
	enum class SystemPipeLineStateType
	{
		/* �|�X�g�G�t�F�N�g */
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

		/* ���b�V���`�� */
		SimpleMesh,
		SkinningMesh,
		InvertSimpleMesh,
		InvertSkinningMesh,
		MonoColorSimpleMesh,
		MonoColorSkinningMesh,
		MonoColorSimpleMeshWireFrame,
		MonoColorSkinningMeshWireFrame,

		/* ���b�V���V���h�E�}�b�v�`�� */
		SimpleMeshShadowMap,
		SkinningMeshShadowMap,
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_