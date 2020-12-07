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

	// 「PostEffectMaterialData」を管理するクラス
	class PostEffectMaterialManager
	{
	public:

		explicit PostEffectMaterialManager(const PostEffectMaterialManagerInitParam& initParam);
		~PostEffectMaterialManager();

	public:

		// 「PostEffectMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const PostEffectMaterialInitParam& initParam);

		// 指定したポストエフェクトを描画する
		void drawPostEffect(size_t handle, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

		// 指定したポストエフェクトマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addPostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamInitParam& initParam);

		// 指定したポストエフェクトマテリアルで追加で管理する定数バッファの値を更新する
		void updatePostEffectMaterialAppendParam(size_t handle, const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		tktkContainer::ResourceContainer<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
