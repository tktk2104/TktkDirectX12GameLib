#ifndef DX_GAME_DRAW_FUNC_ARGS_H_
#define DX_GAME_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// DirectX12���g�p�����`��ɋ��ʂ��ėv�������ϐ�
	struct DXGameDrawFuncArgs
	{
		// �g�p����r���[�|�[�g��ID
		size_t viewportHandle;

		// �g�p����V�[�U�[��`��ID
		size_t scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�f�B�X�N���v�^�q�[�v��ID
		size_t rtvDescriptorHeapHandle;
	};
}
#endif // !DX_GAME_DRAW_FUNC_ARGS_H_