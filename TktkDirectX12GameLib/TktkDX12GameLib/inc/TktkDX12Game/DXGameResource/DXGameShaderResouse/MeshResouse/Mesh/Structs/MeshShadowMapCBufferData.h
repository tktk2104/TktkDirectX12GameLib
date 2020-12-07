#ifndef MESH_SHADOW_MAP_CBUFFER_DATA_H_
#define MESH_SHADOW_MAP_CBUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �V���h�E�}�b�v���g�����`��ɕK�v�ȏ��
	struct MeshShadowMapCBufferData
	{
		// �V���h�E�}�b�v�`��Ɏg�p�����r���[�v���W�F�N�V�����s��
		tktkMath::Matrix4	shadowMapViewProjMat	{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !MESH_SHADOW_MAP_CBUFFER_DATA_H_