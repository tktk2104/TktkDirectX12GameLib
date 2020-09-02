#ifndef MESH_DRAW_FUNC_BASE_ARGS_H_
#define MESH_DRAW_FUNC_BASE_ARGS_H_

#include <array>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MeshTransformCbuffer.h"
#include "MeshShadowMapCBuffer.h"

namespace tktk
{
	// ���b�V���`��ɕK�v�Ȉ���
	struct MeshDrawFuncBaseArgs
	{
		// �g�p����r���[�|�[�g�̃n���h��
		unsigned int			viewportHandle;

		// �g�p����V�U�[��`�̃n���h��
		unsigned int			scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h��
		unsigned int			rtvDescriptorHeapHandle;

		// �g�p����[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�n���h��
		unsigned int			dsvDescriptorHeapHandle;

		// �g�p���郉�C�gID
		unsigned int			lightHandle;
	};
}
#endif // !MESH_DRAW_FUNC_BASE_ARGS_H_