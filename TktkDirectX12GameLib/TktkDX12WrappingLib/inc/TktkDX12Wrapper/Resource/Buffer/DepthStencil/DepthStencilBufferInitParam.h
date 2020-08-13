#ifndef DEPTH_STENCIL_BUFFER_INIT_PARAM_H_
#define DEPTH_STENCIL_BUFFER_INIT_PARAM_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �[�x�X�e���V���o�b�t�@����鎞�ɕK�v�ȕϐ�
	struct DepthStencilBufferInitParam
	{
		tktkMath::Vector2	depthStencilSize;		// �[�x�X�e���V���e�N�X�`���̑傫��
		bool				useAsShaderResource;	// �V�F�[�_�[���\�[�X�Ƃ��Ďg�p���邩�̃t���O
	};
}
#endif // !DEPTH_STENCIL_BUFFER_INIT_PARAM_H_