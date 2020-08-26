#ifndef MESH_TRANSFORM_CBUFFER_H_
#define MESH_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// ���b�V���̍��W�ϊ��p�̒萔�o�b�t�@
	struct MeshTransformCbuffer
	{
		// ���[���h�s��
		tktkMath::Matrix4	worldMatrix		{ tktkMath::Matrix4_v::identity };

		// �r���[�s��
		tktkMath::Matrix4	viewMatrix		{ tktkMath::Matrix4_v::identity };

		// �v���W�F�N�V�����s��
		tktkMath::Matrix4	projectionMatrix{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !MESH_TRANSFORM_CBUFFER_H_