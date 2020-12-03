#ifndef POST_EFFECT_MATERIAL_DATA_H_
#define POST_EFFECT_MATERIAL_DATA_H_

/* class member */
#include <vector>

namespace tktk
{
	struct PostEffectMaterialInitParam;
	struct PostEffectMaterialDrawFuncArgs;

	// ポストエフェクトマテリアルを管理するクラス
	class PostEffectMaterialData
	{
	public:

		explicit PostEffectMaterialData(const PostEffectMaterialInitParam& initParam);
		~PostEffectMaterialData() = default;

		// ムーブコンストラクタ
		PostEffectMaterialData(PostEffectMaterialData&& other) noexcept;

	public:

		// ポストエフェクトを描画する
		void drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		size_t m_usePipeLineStateHandle;
		size_t m_useDescriptorHeapHandle;
		std::vector<size_t> m_autoClearRtvDescriptorHeapHandleArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_