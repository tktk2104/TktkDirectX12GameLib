#ifndef SPRITE_TRANSFORM_CBUFFER_H_
#define SPRITE_TRANSFORM_CBUFFER_H_

namespace tktk
{
	// スプライトの座標変換の定数バッファの情報
	struct SpriteTransformCbuffer
	{
		// ワールド行列（hslsの仕様上、float4x3）
		float				worldMatrix[12]{};
	};
}
#endif // !SPRITE_TRANSFORM_CBUFFER_H_