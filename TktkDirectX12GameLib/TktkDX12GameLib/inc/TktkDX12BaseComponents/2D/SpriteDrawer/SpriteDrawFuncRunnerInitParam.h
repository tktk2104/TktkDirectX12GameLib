#ifndef SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_

namespace tktk
{
	struct SpriteDrawFuncRunnerInitParam
	{
	public:

		static SpriteDrawFuncRunnerInitParam& create();

	public:

		// �`��D��x��ݒ肷��
		SpriteDrawFuncRunnerInitParam& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓|�X�g�G�t�F�N�g�K���Ώ�
		SpriteDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

	private:

		static SpriteDrawFuncRunnerInitParam m_self;

	public:

		float	m_drawPriority				{ 0.0f };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
	};
}
#endif // !SPRITE_DRAW_FUNC_RUNNER_INIT_PARAM_H_