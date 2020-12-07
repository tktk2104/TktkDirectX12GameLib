#ifndef POST_EFFECT_MATERIAL_DATA_H_
#define POST_EFFECT_MATERIAL_DATA_H_

/* std::unordered_map */
#include <unordered_map>

/* class member */
#include <vector>

namespace tktk
{
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;
	class PostEffectMaterialAppendParam;
	struct PostEffectMaterialAppendParamInitParam;
	struct PostEffectMaterialAppendParamUpdateFuncArgs;

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

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̃n���h���ƒl��ݒ肷��
		void addAppendParam(const PostEffectMaterialAppendParamInitParam& initParam);

		// ���̃}�e���A���Œǉ��ŊǗ�����萔�o�b�t�@�̒l���X�V����
		void updateAppendParam(const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		size_t m_usePipeLineStateHandle;
		size_t m_useDescriptorHeapHandle;

		std::vector<size_t>											m_autoClearRtvDescriptorHeapHandleArray;
		std::unordered_map<size_t, PostEffectMaterialAppendParam>	m_appendParamMap;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_