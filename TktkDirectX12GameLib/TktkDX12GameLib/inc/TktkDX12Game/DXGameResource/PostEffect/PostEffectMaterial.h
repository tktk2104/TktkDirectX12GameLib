#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "PostEffectShaderFilePaths.h"
#include "PostEffectMaterialData.h"

namespace tktk
{
	// 「PostEffectMaterialData」を管理するクラス
	class PostEffectMaterial
	{
	public:

		PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~PostEffectMaterial() = default;

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
