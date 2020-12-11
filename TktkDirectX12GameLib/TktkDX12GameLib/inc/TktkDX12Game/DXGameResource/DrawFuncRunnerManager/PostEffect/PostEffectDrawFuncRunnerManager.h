#ifndef POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_
#define POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

#include "../../GameObjectResouse/Component/ComponentPtr.h"

namespace tktk
{
	/* class member */
	class PostEffectDrawFuncRunner;

	/* funcUseType */
	struct PostEffectDrawFuncRunnerInitParam;

	// �|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�̊Ǘ��N���X
	class PostEffectDrawFuncRunnerManager
	{
	public:

		PostEffectDrawFuncRunnerManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~PostEffectDrawFuncRunnerManager();

		PostEffectDrawFuncRunnerManager(const PostEffectDrawFuncRunnerManager& other) = delete;
		PostEffectDrawFuncRunnerManager& operator = (const PostEffectDrawFuncRunnerManager& other) = delete;

	public:

		// �������瑶�݂���|�X�g�G�t�F�N�g�̕`��֐������
		void createSystemResource();

		// �V���ȃ|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�����A���̃n���h����Ԃ�
		size_t create(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g�����s�J�n����i���̃|�X�g�G�t�F�N�g�͒�~����j
		void startPostEffect(size_t handle);

		// �S�Ẵ|�X�g�G�t�F�N�g���~����
		void stopPostEffect();

	private:

		void createDrawGameAreaDrawFuncRunner();

		void createNotPostEffectDrawFuncRunner();

		void createPostEffectMonochromeDrawFuncRunner();

		void createPostEffectNegativeDrawFuncRunner();

		void createPostEffectAveragingBlurDrawFuncRunner();

		void createPostEffectEmbossDrawFuncRunner();

		void createPostEffectSharpnessDrawFuncRunner();

	private:

		// �`��G���A�`��p�̃|�X�g�G�t�F�N�g
		tktk::ComponentPtr<PostEffectDrawFuncRunner> m_drawGameAreaDrawFuncRunner;

		// �����������s��Ȃ��|�X�g�G�t�F�N�g�̎��s�R���|�[�l���g
		tktk::ComponentPtr<PostEffectDrawFuncRunner> m_notPostEffectDrawFuncRunner;

		tktkContainer::ResourceContainer<tktk::ComponentPtr<PostEffectDrawFuncRunner>> m_drawFuncRunnerList;
	};
}
#endif // !POST_EFFECT_DRAW_FUNC_RUNNER_MANAGER_H_