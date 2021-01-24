#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

/* class member */
#include <map>
#include <TktkMath/Structs/Vector2.h>
#include "Structs/TempSpriteMaterialInstanceData.h"
#include "Structs/SpriteMaterialInstanceData.h"

namespace tktk
{
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;

	// スプライトのマテリアルを管理するクラス
	class SpriteMaterialData
	{
	public:

		explicit SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData();

		// ムーブコンストラクタ
		SpriteMaterialData(SpriteMaterialData&& other) noexcept;

	public:

		// スプライトが使用するテクスチャのサイズを取得する
		const tktkMath::Vector2& getSpriteTextureSize() const;

		// 最大のインスタンス数を取得する
		size_t getMaxInstanceCount() const;

		// 現在のインスタンス数を取得する
		size_t getCurInstanceCount() const;

		// スプライトをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam();

		// スプライトをインスタンス描画する時に使用する値を追加する
		void addInstanceParam(float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// スプライトをインスタンス描画する時に使用する値を頂点バッファに書き込む
		void updateInstanceParam();

		// スプライトを描画する
		void draw(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// 作ったスプライトのディスクリプタヒープのハンドル
		size_t m_createDescriptorHeapHandle			{ 0U };

		// インスタンス情報を扱う頂点バッファのハンドル
		size_t m_instanceParamVertexBufferHandle	{ 0U };

		// インスタンス情報を扱う頂点バッファを更新するバッファのハンドル
		size_t m_instanceParamUplaodBufferHandle	{ 0U };

		// テクスチャサイズ
		tktkMath::Vector2 m_textureSize;

		// インスタンス描画する時の最大インスタンス数
		size_t m_maxInstanceCount;

		// 一度に描画するインスタンス数
		size_t m_instanceCount{ 0U };

		// インスタンス情報の連想配列
		std::multimap<float, SpriteMaterialInstanceData>	m_instanceParamList;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_