#ifndef SPRITE_TRANSFORM_CBUFFER_H_
#define SPRITE_TRANSFORM_CBUFFER_H_

#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// スプライトの座標変換の定数バッファの情報
	struct SpriteTransformCbuffer
	{
		// ワールド行列（hslsの仕様上、float4x3）
		float				worldMatrix[12]		{};

		// テクスチャUVのオフセット値
		tktkMath::Vector2	textureUvOffset		{ tktkMath::Vector2_v::zero };

		// テクスチャUVに乗算する値
		tktkMath::Vector2	textureUvMulRate	{ tktkMath::Vector2_v::zero };

		// テクスチャのサイズ（ピクセル）
		tktkMath::Vector2	textureSize			{ tktkMath::Vector2_v::one };

		// スプライトの中心点（割合）
		tktkMath::Vector2	spriteCenterRate	{ tktkMath::Vector2_v::zero };
	};
}
#endif // !SPRITE_TRANSFORM_CBUFFER_H_