#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// �|�X�g�G�t�F�N�g��`�悷�鎞�ɕK�v�Ȉ���
	struct PostEffectMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�g�n���h��
		size_t		viewportHandle;

		// �g�p����V�U�[��`�n���h��
		size_t		scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�f�B�X�N���v�^�q�[�v�n���h��
		size_t		rtvDescriptorHeapHandle;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
