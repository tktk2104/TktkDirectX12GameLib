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

	private:

		tktkContainer::ResourceContainer<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
