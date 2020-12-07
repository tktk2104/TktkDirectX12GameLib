#ifndef POST_EFFECT_MATERIAL_APPEND_PARAM_H_
#define POST_EFFECT_MATERIAL_APPEND_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	struct PostEffectMaterialAppendParamInitParam;
	struct PostEffectMaterialAppendParamUpdateFuncArgs;

	// ポストエフェクトマテリアルの追加パラメータ
	class PostEffectMaterialAppendParam
	{
	public:

		PostEffectMaterialAppendParam(const PostEffectMaterialAppendParamInitParam& initParam);
		~PostEffectMaterialAppendParam();

		// ムーブコンストラクタ
		PostEffectMaterialAppendParam(PostEffectMaterialAppendParam&& other) noexcept;

	public:

		// 定数バッファを更新する内容の変数を書き換える
		void updateParam(const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// 定数バッファを更新する
		void updateCbuffer() const;

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		// 定数バッファにコピーする為のバッファハンドル
		size_t	m_createUploadBufferHandle{ 0U };

		// 変更対象の定数バッファハンドル
		size_t	m_cbufferHandle;

		// 定数バッファの大きさ
		size_t	m_dataSize;

		// 定数バッファを更新する内容の変数のポインタ
		std::shared_ptr<void> m_dataTopPos;
	};
}
#endif // !POST_EFFECT_MATERIAL_APPEND_PARAM_H_