#ifndef DRAW_FUNC_RUNNER_MANAGER_H_
#define DRAW_FUNC_RUNNER_MANAGER_H_

/* std::unique_ptr */
#include <memory>

namespace tktk
{
	/* class member */
	class PostEffectDrawFuncRunnerManager;
	//class BillboardDrawFuncRunnerManager;
	//class MeshDrawFuncRunnerManager;

	/* funcUseType */
	struct DrawFuncRunnerManagerInitParam;
	struct PostEffectDrawFuncRunnerInitParam;

	// �`��֐����s�R���|�[�l���g���Ǘ�����N���X
	class DrawFuncRunnerManager
	{
	public:

		explicit DrawFuncRunnerManager(const DrawFuncRunnerManagerInitParam& initParam);
		~DrawFuncRunnerManager();

	public: /* �|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�̏��� */

		// �������瑶�݂���|�X�g�G�t�F�N�g�̕`��֐������
		void createSystemPostEffectDrawFuncRunner();

		// �V���ȃ|�X�g�G�t�F�N�g�̕`��֐����ĂԃR���|�[�l���g�����A���̃n���h����Ԃ�
		size_t createPostEffectDrawFuncRunner(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g�����s�J�n����i���̃|�X�g�G�t�F�N�g�͒�~����j
		void startPostEffect(size_t handle);

		// �S�Ẵ|�X�g�G�t�F�N�g���~����
		void stopPostEffect();

	private:

		std::unique_ptr<PostEffectDrawFuncRunnerManager>	m_postEffectDrawFuncRunnerManager;
		//std::unique_ptr<BillboardDrawFuncRunnerManager>		m_billboardDrawFuncRunnerManager;
		//std::unique_ptr<MeshDrawFuncRunnerManager>			m_meshDrawFuncRunnerManager;
	};
}
#endif // !DRAW_FUNC_RUNNER_MANAGER_H_