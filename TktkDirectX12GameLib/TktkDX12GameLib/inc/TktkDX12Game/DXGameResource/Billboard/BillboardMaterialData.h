#ifndef BILLBOARD_MATERIAL_DATA_H_
#define BILLBOARD_MATERIAL_DATA_H_

#include "BillboardMaterialInitParam.h"
#include "BillboardDrawFuncBaseArgs.h"
#include "BillboardClippingParam.h"
#include "BillboardTransformCbufferUpdateFuncArgs.h"

namespace tktk
{
	class BillboardMaterialData
	{
	public:

		explicit BillboardMaterialData(const BillboardMaterialInitParam& initParam);
		~BillboardMaterialData();

		// ムーブコンストラクタ
		BillboardMaterialData(BillboardMaterialData&& other) noexcept;

	public:

		// ビルボードを描画する
		void drawBillboard(const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateTransformCbuffer(unsigned int copyBufferHandle, const BillboardTransformCbufferUpdateFuncArgs& updateArgs) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateTransformCbufferUseClippingParam(unsigned int copyBufferHandle, const BillboardTransformCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;
	
	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		unsigned int		m_createDescriptorHeapHandle{ 0U };
		unsigned int		m_createCopyBufferHandle{ 0U };
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
	};
}
#endif // !BILLBOARD_MATERIAL_DATA_H_