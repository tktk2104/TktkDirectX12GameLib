#ifndef SYSTEM_CBUFFER_TYPE_H_
#define SYSTEM_CBUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���萔�o�b�t�@�̎��
	enum class SystemCBufferType
	{
		SpriteTransform = 0U,
		SpriteMaterial,
		Line2D,
		Billboard,
		MeshTransform,
		MeshShadowMap,
		BoneMatCbuffer,
		Light,
		BasicMeshMaterial,
		BasicMonoColorMeshCbuffer
	};
}
#endif // !SYSTEM_CBUFFER_TYPE_H_