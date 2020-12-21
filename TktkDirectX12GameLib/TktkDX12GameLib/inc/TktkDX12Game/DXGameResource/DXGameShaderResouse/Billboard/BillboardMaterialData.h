#ifndef BILLBOARD_MATERIAL_DATA_H_
#define BILLBOARD_MATERIAL_DATA_H_

/* class member */
#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>
#include "Structs/BillboardMaterialInstanceVertData.h"

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
		void addInstanceParam(const BillboardMaterialInstanceVertData& instanceParam);

		// ビルボードをインスタンス描画する時に使用する値をｚソートして頂点バッファに書き込む
		void updateInstanceParam(const tktkMath::Matrix4& viewProjMatrix);

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
		std::forward_list<BillboardMaterialInstanceVertData>	m_instanceParamList;
	};
}
#endif // !BILLBOARD_MATERIAL_DATA_H_