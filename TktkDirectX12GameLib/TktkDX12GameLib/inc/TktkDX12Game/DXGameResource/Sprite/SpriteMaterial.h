#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "SpriteMaterialData.h"

namespace tktk
{
	// 「SpriteMaterialData」を管理するクラス
	class SpriteMaterial
	{
	public:

		SpriteMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int spriteMaterialNum);
		~SpriteMaterial() = default;

	public:

		// 「SpriteMaterialData」のインスタンスを作る
		void create(unsigned int id, const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(unsigned int id, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// スプライト描画用のルートシグネチャを作る
		void createRootSignature() const;

		// スプライト描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::HeapArray<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_