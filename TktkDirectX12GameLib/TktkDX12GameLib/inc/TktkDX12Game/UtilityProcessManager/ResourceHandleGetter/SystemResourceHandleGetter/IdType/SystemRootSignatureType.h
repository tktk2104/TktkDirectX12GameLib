#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��郋�[�g�V�O�l�`���̎��
	enum class SystemRootSignatureType
	{
		/* �|�X�g�G�t�F�N�g */
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

		/* ���b�V���`�� */
		SimpleMesh,
		SkinningMesh,
		InvertSimpleMesh,
		InvertSkinningMesh,
		MonoColorSimpleMesh,
		MonoColorSkinningMesh,

		/* ���b�V���V���h�E�}�b�v�`�� */
		SimpleMeshShadowMap,
		SkinningMeshShadowMap,
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_