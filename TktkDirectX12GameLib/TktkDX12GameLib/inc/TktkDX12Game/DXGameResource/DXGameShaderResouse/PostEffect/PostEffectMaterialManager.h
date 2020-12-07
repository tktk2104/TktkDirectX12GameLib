#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	struct PostEffectMaterialManagerInitParam;
	class PostEffectMaterialData;
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;
	struct PostEffectMaterialAppendParamInitParam;
	struct PostEffectMaterialAppendParamUpdateFuncArgs;

	// �uPostEffectMaterialData�v���Ǘ�����N���X
	class PostEffectMaterialManager
	{
	public:

		explicit PostEffectMaterialManager(const PostEffectMaterialManagerInitParam& initParam);
		~PostEffectMaterialManager();

	public:

		// �uPostEffectMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const PostEffectMaterialInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

		// �w�肵���|�X�g�G�t�F�N�g�}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam);

		// �w�肵���|�X�g�G�t�F�N�g�}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̒l���X�V����
		void updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		tktkContainer::ResourceContainer<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
