#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	struct SpriteMaterialManagerInitParam;
	struct ShaderFilePaths;
	class SpriteMaterialData;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct SpriteCbufferUpdateFuncArgs;
	struct SpriteClippingParam;

	// 「SpriteMaterialData」を管理するクラス
	class SpriteMaterialManager
	{
	public:

		SpriteMaterialManager(const SpriteMaterialManagerInitParam& initParam);
		~SpriteMaterialManager();

	public:

		// 「SpriteMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const SpriteMaterialInitParam& initParam);

		// 指定したスプライトを描画する
		void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const;

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