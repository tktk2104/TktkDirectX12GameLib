#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct PostEffectDrawFuncRunnerInitParam
	{
	public:

		static PostEffectDrawFuncRunnerInitParam& create();

	public:

		static PostEffectDrawFuncRunnerInitParam m_self;

	private:

		PostEffectDrawFuncRunnerInitParam() = default;

	public:

		// �`��D��x
		float	drawPriority				{ 1000.0f };

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h��
		// �������p�����[�^�̓Q�[���`��G���A
		size_t	rtvDescriptorHeapHandle		{ 0U };
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_INIT_PARAM_H_