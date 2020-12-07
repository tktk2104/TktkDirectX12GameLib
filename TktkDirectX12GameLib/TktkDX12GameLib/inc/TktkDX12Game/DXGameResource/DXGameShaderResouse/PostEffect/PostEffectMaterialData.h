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

		// このマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addAppendParam(const PostEffectMaterialAppendParamInitParam& initParam);

		// このマテリアルで追加で管理する定数バッファの値を更新する
		void updateAppendParam(const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		size_t m_usePipeLineStateHandle;
		size_t m_useDescriptorHeapHandle;

		std::vector<size_t>											m_autoClearRtvDescriptorHeapHandleArray;
		std::unordered_map<size_t, PostEffectMaterialAppendParam>	m_appendParamMap;
	};
}
#endif // !POST_EFFECT_MATERIAL_DATA_H_