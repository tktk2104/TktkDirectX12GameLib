#ifndef SPRITE_CONSTANT_BUFFER_DATA_H_
#define SPRITE_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// スプライト描画に使用する定数バッファ情報
	struct SpriteConstantBufferData
	{
		// ワールド行列（hslsの仕様上、float4x3）
		float				worldMatrix[12]		{};

		// ブレンドレート
		tktkMath::Color		blendRate			{ 1.0f, 1.0f, 1.0f, 1.0f };

		// テクスチャUVのオフセット値
		tktkMath::Vector2	textureUvOffset		{ 0.0f, 0.0f };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate	{ 0.0f, 0.0f };

		// テクスチャのサイズ（ピクセル）
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	spriteCenterRate	{ 0.0f, 0.0f };

		// スクリーンサイズ
		tktkMath::Vector2	screenSize			{ 640.0f, 480.0f };

		// パディング
		float				pad[2]				{};
	};
}
#endif // !SPRITE_CONSTANT_BUFFER_DATA_H_