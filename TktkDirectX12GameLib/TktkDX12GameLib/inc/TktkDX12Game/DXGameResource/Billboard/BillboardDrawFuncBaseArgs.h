#ifndef BILLBOARD_DRAW_FUNC_BASE_ARGS_H_
#define BILLBOARD_DRAW_FUNC_BASE_ARGS_H_

namespace tktk
{
	struct BillboardDrawFuncBaseArgs
	{
		// �g�p����r���[�|�[�g�̃n���h��
		unsigned int			viewportHandle;

		// �g�p����V�U�[��`�̃n���h��
		unsigned int			scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h��
		unsigned int			rtvDescriptorHeapHandle;

		// �g�p����[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�n���h��
		unsigned int			dsvDescriptorHeapHandle;
	};
}
#endif // !BILLBOARD_DRAW_FUNC_BASE_ARGS_H_