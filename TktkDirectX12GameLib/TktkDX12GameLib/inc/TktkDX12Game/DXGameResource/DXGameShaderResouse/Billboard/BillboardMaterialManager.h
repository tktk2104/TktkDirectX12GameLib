#ifndef BILLBOARD_MATERIAL_H_
#define BILLBOARD_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	struct BillboardMaterialManagerInitParam;
	struct ShaderFilePaths;
	class BillboardMaterialData;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardCbufferUpdateFuncArgs;
	struct BillboardClippingParam;

	// 「BillboardMaterialData」を管理するクラス
	class BillboardMaterialManager
	{
	public:

		BillboardMaterialManager(const BillboardMaterialManagerInitParam& initParam);
		~BillboardMaterialManager();

	public:

		// 「BillboardMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const BillboardMaterialInitParam& initParam);

		// 指定したビルボードを描画する
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateTransformCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

	private:

		// ビルボード描画用のルートシグネチャを作る
		void createRootSignature() const;

		// ビルボード描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths & shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<BillboardMaterialData> m_billboardMaterialArray;
	};
}
#endif // !BILLBOARD_MATERIAL_H_