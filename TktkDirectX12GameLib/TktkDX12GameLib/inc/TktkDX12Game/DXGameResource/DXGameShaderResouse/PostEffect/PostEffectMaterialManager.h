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

	private:

		tktkContainer::ResourceContainer<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_