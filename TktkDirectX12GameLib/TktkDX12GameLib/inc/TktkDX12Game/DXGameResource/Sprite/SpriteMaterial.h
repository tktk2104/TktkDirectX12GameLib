#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "SpriteMaterialData.h"

namespace tktk
{
	// 「SpriteMaterialData」を管理するクラス
	class SpriteMaterial
	{
	public:

		SpriteMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~SpriteMaterial() = default;

	public:

		// 「SpriteMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// スプライト描画用のルートシグネチャを作る
		void createRootSignature() const;

		// スプライト描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_