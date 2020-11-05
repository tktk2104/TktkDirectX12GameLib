#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "PostEffectShaderFilePaths.h"
#include "PostEffectMaterialData.h"

namespace tktk
{
	// �uPostEffectMaterialData�v���Ǘ�����N���X
	class PostEffectMaterial
	{
	public:

		PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~PostEffectMaterial() = default;

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
