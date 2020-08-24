#ifndef POST_EFFECT_MATERIAL_H_
#define POST_EFFECT_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "PostEffectShaderFilePaths.h"
#include "PostEffectMaterialData.h"

namespace tktk
{
	// 「PostEffectMaterialData」を管理するクラス
	class PostEffectMaterial
	{
	public:

		PostEffectMaterial(const PostEffectShaderFilePaths& shaderFilePaths, unsigned int postEffectMaterialNum);
		~PostEffectMaterial() = default;

	public:

		// 「PostEffectMaterialData」のインスタンスを作る
		void create(unsigned int id, const PostEffectMaterialInitParam& initParam);

		// 指定したポストエフェクトを描画する
		void drawPostEffect(unsigned int id, const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		tktkContainer::HeapArray<PostEffectMaterialData> m_postEffectMaterialArray;
	};
}
#endif // !POST_EFFECT_MATERIAL_H_
