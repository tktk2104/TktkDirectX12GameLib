#ifndef POST_EFFECT_MATERIAL_DATA_H_
#define POST_EFFECT_MATERIAL_DATA_H_

/* class member */
#include <vector>

namespace tktk
{
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;

	// �|�X�g�G�t�F�N�g�}�e���A�����Ǘ�����N���X
	class PostEffectMaterialData
	{
	public:

		explicit PostEffectMaterialData(const PostEffectMaterialInitParam& initParam);
		~PostEffectMaterialData() = default;

		// ���[�u�R���X�g���N�^
		PostEffectMaterialData(PostEffectMaterialData&& other) noexcept;

	public:

		// �|�X�g�G�t�F�N�g��`�悷��
		void drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		size_t m_usePipeLineStateHandle;
		size_t m_useDescriptorHeapHandle;
		std::vector<size_t> m_autoClearRtvDescriptorHeapHandleArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_