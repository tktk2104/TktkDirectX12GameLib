#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

#include <TktkMath/Structs/Matrix3.h>
#include "SpriteMaterialInitParam.h"
#include "SpriteMaterialDrawFuncArgs.h"

namespace tktk
{
	// スプライトのマテリアルを管理するクラス
	class SpriteMaterialData
	{
	public:

		explicit SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData();

		// ムーブコンストラクタ
		SpriteMaterialData(SpriteMaterialData&& other) noexcept;

	public:

		// スプライトを描画する
		void drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		unsigned int		m_createDescriptorHeapHandle { 0U };
		unsigned int		m_createCopyBufferHandle{ 0U };
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
		tktkMath::Vector2	m_spriteCenterRate;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_