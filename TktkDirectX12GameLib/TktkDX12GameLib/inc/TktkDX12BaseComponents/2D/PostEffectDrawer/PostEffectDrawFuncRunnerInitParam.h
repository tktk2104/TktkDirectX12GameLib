#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct PostEffectDrawFuncRunnerInitParam
	{
		// �`��D��x
		float	drawPriority				{ 10000.0f };

		// �`���̃����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h��
		size_t	rtvDescriptorHeapHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_