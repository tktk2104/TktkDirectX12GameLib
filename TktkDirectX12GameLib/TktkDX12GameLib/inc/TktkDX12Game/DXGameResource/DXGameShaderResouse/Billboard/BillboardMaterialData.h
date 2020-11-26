#ifndef BILLBOARD_MATERIAL_DATA_H_
#define BILLBOARD_MATERIAL_DATA_H_

/* class member */
#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include "BillboardMaterialInstanceVertData.h"

namespace tktk
{
	/* funcUseType */
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;

	// ビルボードマテリアルの情報を扱うクラス
	class BillboardMaterialData
	{
	public:

		explicit BillboardMaterialData(const BillboardMaterialInitParam& initParam);
		~BillboardMaterialData();

		// ムーブコンストラクタ
		BillboardMaterialData(BillboardMaterialData&& other) noexcept;

	public:

		// ビルボードテクスチャのサイズを取得する
		const tktkMath::Vector2& getBillboardTextureSize() const;

		// ビルボードをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam();

		// ビルボードをインスタンス描画する時に使用する値を追加する
		void addInstanceVertParam(const BillboardMaterialInstanceVertData& instanceParam);

		// インスタンス描画情報を扱う頂点バッファを更新する
		void updateInstanceParamVertBuffer() const;

		// ビルボードを描画する
		void draw(const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

	private:

		// 作ったビルボードのディスクリプタヒープのハンドル
		size_t m_createDescriptorHeapHandle	{ 0U };
		
		// インスタンス情報を扱う頂点バッファのハンドル
		size_t m_instanceParamVertexBufferHandle{ 0U };

		// テクスチャサイズ
		tktkMath::Vector2 m_textureSize;

		// インスタンス描画する時の最大インスタンス数
		size_t m_maxInstanceCount;

		// 一度に描画するインスタンス数
		size_t m_instanceCount				{ 0U };

		// 加算ブレンドを行うか？
		bool m_isEffect;

		// インスタンス情報の配列
		std::forward_list<BillboardMaterialInstanceVertData>	m_instanceVertParamList;
	};
}
#endif // !BILLBOARD_MATERIAL_DATA_H_