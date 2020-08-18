#ifndef DX_GAME_DRAW_FUNC_ARGS_H_
#define DX_GAME_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// DirectX12���g�p�����`��ɋ��ʂ��ėv�������ϐ�
	struct DXGameDrawFuncArgs
	{
		// �g�p����r���[�|�[�g��ID
		unsigned int viewportId;

		// �g�p����V�[�U�[��`��ID
		unsigned int scissorRectId;

		// �g�p���郌���_�[�^�[�Q�b�g�p�f�B�X�N���v�^�q�[�v��ID
		unsigned int rtvDescriptorHeapId;
	};
}
#endif // !DX_GAME_DRAW_FUNC_ARGS_H_