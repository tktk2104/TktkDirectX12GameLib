#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

#include <TktkMath/Structs/Matrix3.h>
#include "SpriteMaterialInitParam.h"
#include "SpriteMaterialDrawFuncArgs.h"
#include "SpriteClippingParam.h"

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

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する
		void updateTransformCbuffer(size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate) const;

		// 引数が表すコピーバッファを使って座標変換情報を管理する定数バッファを更新する（切り抜き範囲指定版）
		void updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const tktkMath::Matrix3& worldMatrix, const tktkMath::Vector2& spriteCenterRate, const SpriteClippingParam& clippingParam) const;

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		size_t				m_createDescriptorHeapHandle { 0U };
		size_t				m_createUploadBufferHandle{ 0U };
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_