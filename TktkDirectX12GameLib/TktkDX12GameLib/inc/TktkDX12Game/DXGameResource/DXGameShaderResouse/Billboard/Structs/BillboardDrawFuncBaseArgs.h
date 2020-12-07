#ifndef BILLBOARD_DRAW_FUNC_BASE_ARGS_H_
#define BILLBOARD_DRAW_FUNC_BASE_ARGS_H_

namespace tktk
{
	// �r���{�[�h�̕`��ɕK�v�ȕϐ�
	struct BillboardDrawFuncBaseArgs
	{
		// �g�p����r���[�|�[�g�̃n���h��
		size_t	viewportHandle;

		// �g�p����V�U�[��`�̃n���h��
		size_t	scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h��
		size_t	rtvDescriptorHeapHandle;

		// �g�p����[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�n���h��
		size_t	dsvDescriptorHeapHandle;
	};
}
#endif // !BILLBOARD_DRAW_FUNC_BASE_ARGS_H_